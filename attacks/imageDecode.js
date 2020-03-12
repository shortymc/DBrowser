var res_array = [];
var count = {};
var payload = 105; 
var cur = 0;
var pre_start = 0;
var ran = 0;
var avg = [];

function run(file_name) {
  console.log('begin');
  var element_s = document.createElement('img');
  //document.getElementById("extra").innerHTML += start + ',';
  document.body.appendChild(element_s);
  start = performance.now();
  element_s.onerror = function() {
    cur ++;
    var end = performance.now();
    var res = end - start;
    console.log(start, end, end-start);
    //document.getElementById("extra").innerHTML += start + ',' + end + ',' + res + '<br>';
    if(addToRes(res)) run(file_name);
  }
  element_s.src = "http://127.0.0.1:8081/" + file_name;
  //element_s.src = "https://www.google.com/logos/doodles/2017/esther-afua-ocloos-98th-birthday-5995813305057280-l.png";

}


function addToRes(during) {
  if(cur > 4 && cur < payload){
    res_array.push([cur-4, during]); 
    if(count[during] === undefined)count[during] = 0;
    count[during] += 1;
  }
  if(cur >= payload) {
    get_res();
    document.getElementById("info").innerHTML = "We have " + Object.keys(count).length + " different times<br>";
    for(key in count) {
      document.getElementById("info").innerHTML += key + ': ' + count[key] + '<br>';
    }
    
    document.getElementById("info").innerHTML += 'The times are here<br>' + res_array.join('<br>');
    return false;
  }
  return true;
}

function get_res() {
  var mean = 0;
  for(var r in res_array) {
    mean += res_array[r][1];
  }
  mean /= res_array.length;
  //document.getElementById("result").innerHTML += mean.toString() + '<br>';
  return mean;
}

function doJob() {
  for(var i = 9;i < 10; i++) {
    var average = run(i.toString() + "e5.png");
    //var average = run("https://www.google.com/logos/doodles/2017/esther-afua-ocloos-98th-birthday-5995813305057280-l.png");
    res_array = [];
    avg.push([i, average]);
  }
  return avg;
}