
/*
  AUTHORS :
    IORIO MATTEO
    VINCENZI FABIO
*/
// Labels
const label_seconds = document.getElementById("lbl_seconds");
const label_led = document.getElementById("lbl_led");
const label_servo = document.getElementById("lbl_servo");
const slider = document.getElementById("slider_angle");
// Buttons for refresh 
const btn_seconds = document.getElementById("get_seconds"); 
//const btn_get_led = document.getElementById("get_led");
//const btn_get_servo = document.getElementById("get_servo");
// Manage the Room Controller
const btn_set_led_on = document.getElementById("set_led_on");
const btn_set_led_off = document.getElementById("set_led_off");
const btn_set_servo = document.getElementById("set_servo");

btn_seconds.addEventListener("click", e =>{
    let seconds = 0;
    axios.get("http://127.0.0.100:5000/api/data").then(function (response) {
        seconds = response["data"]["seconds"];
        label_seconds.innerHTML = `Light on for : ${seconds} s all day`;
    });    
});
/*
btn_get_led.addEventListener("click", e=> {
    let state = "";
    axios.get('http://127.0.0.100:5000/api/led').then(function (response) {
        state = response["data"]["state"];
        label_led.innerHTML = `Led's state : ${state}`;
    });
});

btn_get_servo.addEventListener("click", e => {
    let angle = 0;
    axios.get(`http://127.0.0.100:5000/api/servo`).then(function (response) {
        angle = response["data"]["angle"];
        label_servo.innerHTML = `Servo's angle : ${angle}`;
    });
});
*/
btn_set_led_on.addEventListener("click", e => {
    axios.get('http://127.0.0.100:5000/api/led?state=ON').then(function(response){
        state = response["data"]["state"];
        label_led.innerHTML = `Led's state : ${state}`;
    })
});

btn_set_led_off.addEventListener("click", e => {
    axios.get(`http://127.0.0.100:5000/api/led?state=OFF`)
    .then(function(response){
        state = response["data"]["state"];
        label_led.innerHTML = `Led's state : ${state}`;
    });
});

btn_set_servo.addEventListener("click", e => {
    let input_angle = slider.value;
    axios.get(`http://127.0.0.100:5000/api/servo?angle=${input_angle}`)
    .then(function(response){
        let angle = response["data"]["angle"];
        label_servo.innerHTML = `Servo's angle : ${angle}`;
    });
});
