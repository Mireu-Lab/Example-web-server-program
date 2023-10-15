const express = require("express")
const app = express()
const port = 8080;

app.get("/", (req, res) => {
    res.sendfile("templates/index.html");
});

app.listen(port, (err) => {
    console.log(`The server is listening on port ${port}`)
})