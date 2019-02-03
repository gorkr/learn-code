/**
 * 一个简单的http服务器
 * @type {[type]}
 */

/*
var http = require("http");  //这把我们的本地变量`http`变成了一个拥有所有 http 模块所提供的公共方法的对象。

//这里用了js的函数传递
//在JavaScript中，一个函数可以作为另一个函数接收一个参数。我们可以先定义一个函数，然后传递，也可以在传递参数的地方直接定义函数。
http.createServer(function(request, response) {
  response.writeHead(200, {"Content-Type": "text/plain"});
  response.write("Hello World");
  response.end();
}).listen(8888);// 监听8888端口
*/

var http = require("http");
var url = require("url");

function start(route, handle){
  function onRequest(request, response) {
    var pathname = url.parse(request.url).pathname;
    console.log("Request for" + pathname +" received.");

    route(handle, pathname, response);

    //response.writeHead(200, {"Content-Type": "text/plain"});//响应报头
    //var content = route(handle, pathname);
    //response.write(content);//响应主体
    //response.end();
  }

  http.createServer(onRequest).listen(8888);
  console.log("Server has started.");
}
exports.start = start;  //导出start
