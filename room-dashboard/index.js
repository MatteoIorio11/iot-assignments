const options = {
    headers: {'Access-Control-Allow-Origin': '*'}
}

const label_seconds = document.getElementById("lbl_seconds");

document.getElementById("get_seconds").addEventListener("click", e =>{
    let seconds = 0
    axios.get("http://127.0.0.100:5000/api/data").then(function (response) {
        seconds = response["data"]["seconds"];
        label_seconds.innerHTML = `Light on for : ${seconds} s all day`;
    });    
});


/*
axios.get('http://127.0.0.100:5000/api/led').then(function (response) {
    Save the angle got from the server
})
*/


/*
axios.post('http://127.0.0.100:5000/api/led', {
    angle: INPUT_ANGLE,
  })
  .then(function (response) {
    console.log(response);
  })
*/

/*
axios.get('http://127.0.0.100:5000/api/servo').then(function (response) {
    Save the angle got from the server
})
*/


/*
axios.post('http://127.0.0.100:5000/api/servo', {
    angle: INPUT_ANGLE,
  })
  .then(function (response) {
    console.log(response);
  })
*/




