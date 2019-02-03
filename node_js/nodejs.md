# nodejs

主文件叫做*index.js*或多或少是个标准格式（*dex.js* 的文件去调用应用的其他模块（比如 *server.js* 中的HTTP服务器模块）来引导和启动应用。）。把服务器模块放进叫*server.js*的文件里则很好理解。



##### 函数传递

//在JavaScript中，一个函数可以作为另一个函数接收一个参数。我们可以先定义一个函数，然后传递，也可以在传递参数的地方直接定义函数。

```javascript
function execute(someFunction, value) {
  someFunction(value);
}

execute(function(word){ console.log(word) }, "Hello");
```





##### 基于事件驱动的回调

Node.js是事件驱动的

这是异步的：请求任何时候都可能到达，但是我们的服务器却跑在一个单进程中。

我们创建了服务器，并且向创建它的方法传递了一个函数。无论何时我们的服务器收到一个请求，这个函数就会被调用。这个就是传说中的 *回调* 。我们给某个方法传递了一个函数，这个方法在有相应事件发生时调用这个函数来进行 *回调* 。

当有事件发生时，回调就会进行。 就是不论什么时候传入参数，函数都能完整的执行。



##### 模块

```js
var http = require("http");
```

这样就相当于导入了`http`模块，本地变量起一个和模块名称一样的名字是一种惯例。

```js
// server.js
var http = require("http");

function start() {
  function fs(){}
  http.createServer(onRequest).listen(8888);
  console.log("Server has started.");
}

exports.start = start;

//index.js
var server = require("./server");
server.start();
```



##### 路由

处理不同的请求，叫做路由选择。

使用url和querystring模块。



> 在JavaScript中，对象就是一个键/值对的集合 -- 你可以把JavaScript的对象想象成一个键为字符串类型的字典。

> 但如果JavaScript的对象仅仅是键/值对的集合，它又怎么会拥有方法呢？好吧，这里的值可以是字符串、数字或者……函数！



server.js ： 服务器， 调用路由

router.js :   根据路径，调用 不用的handle函数。并处理`404`。

~~requestHandler :  将不同的函数与 路径对应， 并被 路由地哦啊用~~

requestHandler:  存储不同的 handle函数 ，~~路径和handle函数的对应关系在index.js中实现~~, 相应内容在handle中实现

##### 阻塞与非阻塞

阻塞调用是指调用结果返回之前，当前线程会被挂起。调用线程只有在得到结果之后才会返回。
非阻塞调用指在不能立刻得到结果之前，该调用不会阻塞当前线程。

用非阻塞操作，我们需要使用回调，通过将函数作为参数传递给其他需要花时间做处理的函数

将函数作为参数传递给其他需要花时间处理的函数。

`exec()`在非阻塞中发挥作用。