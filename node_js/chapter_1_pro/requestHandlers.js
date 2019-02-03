/*
function start(){
  console.log("request start");

  function sleep(milliSeconds){
    var startTime = new Date().getTime();
    while(new Date().getTime() < startTime + milliSeconds);
  }

  sleep(10000);
  return "hello start";
}
*/

var exec = require("child_process").exec;

function start(response) {
  console.log("Request handler 'start' was called.");

  exec("ls -lah", function (error, stdout, stderr) {
    //content = stdout;
    //我们的代码是同步执行的，这就意味着在调用exec()之后，Node.js会立即执行 return content；
    //在这个时候，content仍然是“empty”，因为传递给exec()的回调函数还未执行到——因为exec()的操作是异步的。
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.write(stdout);
    response.end();
  });

  //return content;   所以这里去除return, 就不会再有empty的问题。
}


function upload(response){
  //console.log("upload");
  //return "hello upload";
  console.log("Request handler 'upload' was called.");
  response.writeHead(200, {"Content-Type": "text/plain"});
  response.write("Hello Upload");
  response.end();
}

exports.start = start;
exports.upload = upload;
