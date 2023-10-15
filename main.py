from fastapi.responses import FileResponse
from fastapi import FastAPI

app = FastAPI()

@app.get("/")
async def index():
    return FileResponse("templates/index.html")

while True:
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=80)