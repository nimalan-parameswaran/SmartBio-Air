import azure.functions as func
import logging
import json
import os
import datetime
from openai import AzureOpenAI
from azure.data.tables import TableClient

# Configuration from Environment Variables
OPENAI_ENDPOINT = os.environ.get("AZURE_OPENAI_ENDPOINT")
OPENAI_KEY = os.environ.get("AZURE_OPENAI_KEY")
DEPLOYMENT_NAME = "myosa-agent-model" 
STORAGE_CONN_STR = os.environ.get("AZURE_STORAGE_CONNECTION_STRING")
TABLE_NAME = "SensorHistory"

# Init OpenAI Client
client = None
if OPENAI_ENDPOINT and OPENAI_KEY:
    client = AzureOpenAI(azure_endpoint=OPENAI_ENDPOINT, api_key=OPENAI_KEY, api_version="2023-05-15")

app = func.FunctionApp()

@app.route(route="ProcessSensorData", auth_level=func.AuthLevel.ANONYMOUS)
def ProcessSensorData(req: func.HttpRequest) -> func.HttpResponse:
    logging.info('MYOSA Data Received.')
    try:
        req_body = req.get_json()
    except:
        return func.HttpResponse("Invalid JSON", status_code=400)

    # 1. Archive to Table Storage (Agent 2)
    if STORAGE_CONN_STR:
        try:
            table_client = TableClient.from_connection_string(STORAGE_CONN_STR, TABLE_NAME)
            entity = {
                "PartitionKey": req_body.get('deviceId', 'MYOSA_01'),
                "RowKey": str(datetime.datetime.utcnow().timestamp()),
                "Pressure": str(req_body.get('pressure', 0)),
                "AirQuality_MQ135": int(req_body.get('mq135', 0)),
                "Algae_Green_Index": int(req_body.get('green_light', 0)),
                "Motor_Fault": int(req_body.get('motor_fault', 0))
            }
            table_client.create_entity(entity=entity)
        except Exception as e:
            logging.error(f"Archival Error: {e}")

    # 2. AI Decision (Agent 1)
    # Hardware Override
    if req_body.get('motor_fault') == 1:
        res = {"motor_speed": 0, "ai_summary": "FAULT: Motor Stopped", "algae_state": "Bad", "aq_score": 0, "aq_status": "Error"}
    else:
        try:
            prompt = f"Sensors: MQ135={req_body.get('mq135')}, Green={req_body.get('green_light')}"
            response = client.chat.completions.create(
                model=DEPLOYMENT_NAME,
                messages=[{"role": "system", "content": "You are a MYOSA Algae Controller. Output JSON only: {'motor_speed': int, 'ai_summary': str, 'algae_state': str, 'aq_score': int, 'aq_status': str}"},
                          {"role": "user", "content": prompt}],
                max_tokens=60
            )
            res = json.loads(response.choices[0].message.content.strip().replace("```json", "").replace("```", ""))
        except:
            res = {"motor_speed": 100, "ai_summary": "AI Offline", "algae_state": "OK", "aq_score": 50, "aq_status": "Stable"}

    return func.HttpResponse(json.dumps(res), mimetype="application/json")

@app.route(route="GetDashboardData", auth_level=func.AuthLevel.ANONYMOUS)
def GetDashboardData(req: func.HttpRequest) -> func.HttpResponse:
    try:
        table_client = TableClient.from_connection_string(STORAGE_CONN_STR, TABLE_NAME)
        entities = list(table_client.query_entities(""))
        history = [{"timestamp": e.get("RowKey"), "mq135": e.get("AirQuality_MQ135"), "algae": e.get("Algae_Green_Index")} for e in entities][-50:]
        return func.HttpResponse(json.dumps(history), mimetype="application/json")
    except:
        return func.HttpResponse("[]", mimetype="application/json")