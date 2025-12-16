String homePage = F(R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 Sensor Dashboard</title>

<style>
body {
    background-color: DodgerBlue;
    font-family: Arial;
    color: navy;
    text-align: center;
    margin: 0;
    padding: 0;
}
.flex-Container {
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 20px;
}
h1 {
    font-size: 40px;
}
p {
    font-size: 22px;
}
table {
    font-size: 22px;
    border-collapse: collapse;
    margin-top: 20px;
    width: 80%;
    max-width: 600px;
}
th, td {
    padding: 10px;
    border-bottom: 1px solid #ddd;
    text-align: left;
}
</style>
</head>

<body>
<div class="flex-Container">
<h1>ESP32 Sensor Dashboard</h1>
<p>Live readings from multiple sensors</p>

<table>
<tr>
    <th>Sensor</th>
    <th>Value</th>
    <th>Unit</th>
</tr>
<tr>
    <td>Temperature</td>
    <td id="temp">--</td>
    <td>°C</td>
</tr>
<tr>
    <td>Humidity</td>
    <td id="hum">--</td>
    <td>%</td>
</tr>
<tr>
    <td>PIR Motion</td>
    <td id="pir">--</td>
    <td></td>
</tr>
</table>
</div>

<script>
setInterval(() => {
    fetch("/data")
        .then(response => response.json())
        .then(data => {
            document.getElementById("temp").textContent = data.temp;
            document.getElementById("hum").textContent = data.hum;
            document.getElementById("pir").textContent =
                data.pir == 1 ? "Motion Detected" : "No Motion";
        })
        .catch(err => console.log(err));
}, 2000);
</script>

</body>
</html>
)=====");