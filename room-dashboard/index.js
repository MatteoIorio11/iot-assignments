
console.log("ciao");
const options = {
    headers: {'Access-Control-Allow-Origin': '*'}
}

axios.get("http://127.0.0.100:5000/api/data")
    .then(function (response) {
        console.log(response['data']);
});