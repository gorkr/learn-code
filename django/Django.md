# Django

## 配置

**强烈推荐在 Virtualenv 下进行 Django 的开发。**Virtualenv 是一个 Python 工具，使用它可以创建一个独立的 Python 环境。

```shell
gorkr@gorkr-PC:~/project/django$ virtualenv ~/project/django/
gorkr@gorkr-PC:~/project/django$ source bin/activate
```

```shell
(django) gorkr@gorkr-PC:~/project/django/Workplace$ django-admin startproject blogproject
```

运行 `python manage.py runserver` 命令就可以在本机上开启一个 Web 服务器：

Django 默认的语言是英文的，打开`settings.py`文件。

```vim
# 把英文改为中文
LANGUAGE_CODE = 'zh-hans'

# 把国际时区改为中国时区
TIME_ZONE = 'Asia/Shanghai'
```

## 博客应用

，运行 `python manage.py startapp blog` 命令即可建立一个 blog 应用

然后再主settings下注册blog应用。

## 数据库

客最主要的功能就是展示我们写的文章，它需要从某个地方获取博客文章数据才能把文章展示出来，通常来说这个地方就是数据库。

数据库存储的数据其实就是表格的形式，例如存储博客文章的数据库表长这个样子：

| 文章 id | 标题    | 正文   | 发表时间   | 分类   | 标签        |
| ------- | ------- | ------ | ---------- | ------ | ----------- |
| 1       | title 1 | text 1 | 2016-12-23 | Django | Django 学习 |
| 2       | title 2 | text 2 | 2016-12-24 | Django | Django 学习 |
| 3       | title 3 | text 3 | 2016-12-26 | Python | Python 学习 |

不同的文章可能它们对应的分类或者标签是相同的，所以我们把分类和标签提取出来，做成单独的数据库表，再把文章和分类、标签关联起来。 

| 分类 id | 分类名 |
| ------- | ------ |
| 1       | Django |
| 2       | Python |

| 标签 id | 标签名      |
| ------- | ----------- |
| 1       | Django 学习 |
| 2       | Python 学习 |

 ```python
blog/models.py

from django.db import models

class Category(models.Model):
    name = models.CharField(max_length=100)
    #在数据库里创建一个名为 category 的表格，这个表格的一个列名为 name。还有一个列 id，Django 则会自动创建。
 ```

>Django 内置的全部类型可查看文档：
>https://docs.djangoproject.com/en/1.10/ref/models/fields/#field-types

> **阅读Django 官方文档 [关于字段类型的介绍](https://docs.djangoproject.com/en/1.10/ref/models/fields/) 来了解有哪些数据类型可以使用以及如何使用它们。**

```
根据文章，踩了个坑，建外键时，ForeignKey包含两个参数：

category = models.ForeignKey(Category, on_delete=models.CASCADE)
```

### 迁移数据库

我们已经编写了博客数据库模型的代码，但那还只是 Python 代码而已，Django 还没有把它翻译成数据库语言，因此实际上这些数据库表还没有真正的在数据库中创建

分别运行 `python manage.py makemigrations` 和 `python manage.py migrate`命令。

blog 应用的 migrations\ 目录下生成了一个 0001_initial.py 文件，这个文件是 Django 用来记录我们对模型做了哪些修改的文件。

对于了解数据库语言的人，你可以运行下面的命令看看 Django 究竟为我们做了什么：

```
python manage.py sqlmigrate blog 0001
```

### 选择数据库

 Python 内置的 SQLite3 数据库。

### 用Django的方式操作数据库

#### 存数据

先在命令行中来探索一下这些函数，感受一下如何用 Django 的方式来操作数据库。在 manage.py 所在目录下运行 `python manage.py shell` 命令

```python
>>> from blog.models import Category, Tag, Post
>>> c = Category(name='category test')
>>> c.save()
>>> t = Tag(name='tag test')
>>> t.save()
```

再创建一篇文章试试，但创建文章之前，我们需要先创建一个 User，用于指定文章的作者。创建 User 的命令 Django 已经帮我们写好了，依然是通过 manage.py 来运行。`python manage.py createsuperuser`

```python
>>> from blog.models import Category, Tag, Post
>>> from django.utils import timezone
>>> from django.contrib.auth.models import User

>>> user = User.objects.get(username='myuser')
>>> c = Category.objects.get(name='category test')

>>> p = Post(title='title test', body='body test', created_time=timezone.now(), modified_time=timezone.now(), category=c, author=user)
>>> p.save()
```

#### 取数据

```python
>>> Category.objects.all()
<QuerySet [<Category: Category object>]>
>>> Tag.objects.all()
<QuerySet [<Tag: Tag object>]>
>>> Post.objects.all()
<QuerySet [<Post: Post object>]>
>>>
```

显示的字符串有点奇怪，无法看出究竟是不是我们之前存入的数据。为了让显示出来的数据更加人性化一点，我们为 3 个模型分别增加一个 `__str__` 方法：

```python
blog/models.py

from django.utils.six import python_2_unicode_compatible

# python_2_unicode_compatible 装饰器用于兼容 Python2
@python_2_unicode_compatible
class Category(models.Model):
    ...

    def __str__(self):
        return self.name

@python_2_unicode_compatible
class Tag(models.Model):
    ...

    def __str__(self):
        return self.name

@python_2_unicode_compatible
class Post(models.Model):
    ...

    def __str__(self):
        return self.title
```

```
>>> Post.objects.get(title='title test')
<Post: title test>
```

这里 `all` 方法和 `get` 方法的区别是：`all` 方法返回全部数据，是一个类似于列表的数据结构（QuerySet）；而 `get`返回一条记录数据，如有多条记录或者没有记录，`get` 方法均会抛出相应异常。

 

#### 改数据

```
>>> c = Category.objects.get(name='category test')
>>> c.name = 'category test new'
>>> c.save()
>>> Category.objects.all()
<QuerySet [<Category: test category new>]>
```

#### 删数据

```
>>> p = Post.objects.get(title='title test')
>>> p
<Post: title test>
>>> p.delete()
(1, {'blog.Post_tags': 0, 'blog.Post': 1})
>>> Post.objects.all()
<QuerySet []>
```

## 基础视图 

Web 应用的交互过程其实就是 HTTP 请求与响应的过程

#### 绑定url和视图函数

首先 Django 需要知道当用户访问不同的网址时，应该如何处理这些不同的网址（即所说的路由）。Django 的做法是把不同的网址对应的处理函数写在一个 urls.py 文件里，当用户访问某个网址时，Django 就去会这个文件里找，如果找到这个网址，就会调用和它绑定在一起的处理函数（叫做视图函数）。

**首先在 blog 应用的目录下创建一个 urls.py 文件**



```
blog/urls.py

from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
]
```

第一个参数是网址，第二个参数是处理函数），另外我们还传递了另外一个参数 `name`，这个参数的值将作为处理函数 `index` 的别名

**注意：在项目根目录的 blogproject\ 目录下（即 settings.py 所在的目录），原本就有一个 urls.py 文件，这是整个工程项目的 URL 配置文件。而我们这里新建了一个 urls.py 文件，且位于 blog 应用下。这个文件将用于 blog 应用相关的 URL 配置。不要把两个文件搞混了。**

#### 视图函数

```
blog/views.py

from django.http import HttpResponse

def index(request):
    return HttpResponse("欢迎访问我的博客首页！")
```

#### 项目url

Django 匹配 URL 模式是在 blogproject\ 目录（即 settings.py 文件所在的目录）的 urls.py 下的，所以我们要把 blog 应用下的 urls.py 文件包含到 blogproject\urls.py 里去

```
- from django.conf.urls import url
+ from django.conf.urls import url, include
from django.contrib import admin

urlpatterns = [
    url(r'^admin/', admin.site.urls),
+   url(r'', include('blog.urls')),
]
#这里也可以写其它字符串，Django 会把这个字符串和后面 include 的 urls.py 文件中的 URL 拼接。比如说如果我们这里把 r'' 改成 r'blog/'，而我们在 blog.urls 中写的 URL 是 r'^$'，即一个空字符串。那么 Django 最终匹配的就是 blog/ 加上一个空字符串，即 blog/。
```

####使用Django模板

首先在我们的项目**根目录**（即 manage.py 文件所在目录）下建立一个名为 templates 的文件夹，用来存放我们的模板。然后在 templates\ 目录下建立一个名为 blog 的文件夹，用来存放和 blog 应用相关的模板。

在 templates\blog\index.html 文件里写入下面的代码：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>{{ title }}</title>
</head>
<body>
<h1>{{ welcome }}</h1>
</body>
</html>
```

用 {{ }} 包起来的变量叫做模板变量。Django 在渲染这个模板的时候会根据我们传递给模板的变量替换掉这些变量。

模板写好了，还得告诉 Django 去哪里找模板，在 settings.py 文件里设置一下模板文件所在的路径。在 settings.py 找到 `TEMPLATES` 选项

其中 `DIRS` 就是设置模板的路径，在 [] 中写入 `os.path.join(BASE_DIR, 'templates')`，即像下面这样：

```
blogproject/settings.py

TEMPLATES = [
    {
        ...
        'DIRS': [os.path.join(BASE_DIR, 'templates')],
        ...
    },
]
```

```
blog/views.py

from django.http import HttpResponse
from django.shortcuts import render

def index(request):
    return render(request, 'blog/index.html', context={
                      'title': '我的博客首页', 
                      'welcome': '欢迎访问我的博客首页'
                  })
```

，然后 `render` 根据第二个参数的值 blog/index.html 找到这个模板文件并读取模板中的内容。之后 `render` 根据我们传入的 `context` 参数的值把模板中的变量替换为我们传递的变量的值，`{{ title }}` 被替换成了 `context` 字典中 `title` 对应的值，同理 `{{ welcome }}` 也被替换成相应的值。

## 视图进阶

#### 处理静态文件

我们的项目使用了从网上下载的一套博客模板（[点击这里下载全套模板](https://github.com/zmrenwu/django-blog-tutorial-templates)）。这里面除了 HTML 文档外，还包含了一些 CSS 文件和 JavaScript 文件以让网页呈现出我们现在看到的样式。同样我们需要对 Django 做一些必要的配置，才能让 Django 知道如何在开发服务器中引入这些 CSS 和 JavaScript 文件，这样才能让博客页面的 CSS 样式生效。

把 CSS 和 JavaScript 文件放在 **blog 应用**的 static\ 目录下。因此，先在 **blog 应用**下建立一个 static 文件夹。，为了避免和其它应用中的 CSS 和 JavaScript 文件命名冲突（别的应用下也可能有和 blog 应用下同名的 CSS 、JavaScript 文件），我们再在 static\ 目录下建立一个 blog 文件夹，并存入 css 和 js 文件

你会看到首页显示的样式非常混乱，原因是浏览器无法正确加载 CSS 等样式文件。需要以 Django 的方式来正确地处理 CSS 和 JavaScript 等静态文件的加载路径



我们把引用路径放在了一个奇怪的符号里，例如：href="{% static 'blog/css/bootstrap.min.css' %}"。用 {% %} 包裹起来的叫做模板标签



**为了能在模板中使用 {% static %} 模板标签，别忘了在最顶部 {% load staticfiles %} 。static 模板标签位于 staticfiles 模块中，只有通过 load 模板标签将该模块引入后，才能在模板中使用 {% static %} 标签。**



比如 `{% static 'blog/css/pace.css' %}` 最终渲染的值是 `/static/blog/css/pace.css`。而 /static/ 前缀是我们在 settings.py 文件中通过 `STATIC_URL = '/static/'` 指定的。



####修改模板

目前我们看到的只是模板中预先填充的一些数据，我们得让它显示从数据库中获取的文章数据。

要在模板中使用循环，需要使用到前面提到的模板标签，这次使用 {% for %} 模板标签。将 index.html 中多余的 article 标签删掉，只留下一个 article 标签，然后写上下列代码：

```
templates/blog/index.html

...
{% for post in post_list %}
  <article class="post post-{{ post.pk }}">
    ...
  </article>
{% empty %}
  <div class="no-post">暂时还没有发布的文章！</div>
{% endfor %}
...
```

例如这里的 `{{ post.pk }}`（pk 是 primary key 的缩写，即 post 对应于数据库中记录的 id 值，该属性尽管我们没有显示定义，但是 Django 会自动为我们添加）。

post_list 实在 view.py中定义的， 存储的是所有的post.



## Admin后台

想进入Django Admin 后台，首先需要创建一个超级管理员账户。

 `python manage.py createsuperuser`

##### admin后台注册

要在后台注册我们自己创建的几个模型，这样 Django Admin 才能知道它们的存在，注册非常简单，只需要在 blog\admin.py 中加入下面的代码：

```
blog/admin.py

from django.contrib import admin
from .models import Post, Category, Tag

admin.site.register(Post)
admin.site.register(Category)
admin.site.register(Tag)
```

#### 定制admin

```
from django.contrib import admin
from .models import Post, Category, Tag

class PostAdmin(admin.ModelAdmin):
    list_display = ['title', 'created_time', 'modified_time', 'category', 'author']

# 把新增的 PostAdmin 也注册进来
admin.site.register(Post, PostAdmin)
admin.site.register(Category)
admin.site.register(Tag)
```

## 博客详情页

#### 模板继承

我们看到 index.html 文件和 detail.html 文件除了 main 标签包裹的部分不同外，其它地方都是相同的，我们可以把相同的部分抽取出来，放到 base.html 里。首先在 templates\ 目录下新建一个 base.html 文件



## 支持markdown

将 Markdown 格式的文本渲染成标准的 HTML 文档是一个复杂的工作，好在已有好心人帮我们完成了这些工作使用命令 `pip install markdown` 安装即可。

#### 在 detail 视图中渲染 Markdown

可能想在文章中插入图片，目前能做的且推荐做的是使用外链引入图片。比如将图片上传到七牛云这样的云存储服务器，然后通过 Markdown 的图片语法将图片引入。Markdown 引入图片的语法为：`![图片说明](图片链接)`。



#### safe标签

任何的 HTML 代码在 Django 的模板中都会被转义（即显示原始的 HTML 代码，而不是经浏览器渲染后的格式）。为了解除转义，只需在模板标签使用 `safe` 过滤器即可

`{{ post.body|safe }}`

`pip install pygments` 设置代码高亮。



## 页面侧边栏：使用自定义模板标签



## 表单

当用户提交表单中的数据后，Django 需要调用相应的视图函数来处理这些数据，下面开始写我们视图



这里 `post.comment_set.all()` 也等价于 `Comment.objects.filter(post=post)`，即根据 `post` 来过滤该 `post` 下的全部评论。但既然我们已经有了一个 `Post` 模型的实例 `post`（它对应的是 `Post` 在数据库中的一条记录），那么获取和 `post` 关联的评论列表有一个简单方法，即调用它的 xxx_set 属性来获取一个类似于 objects 的模型管理器，然后调用其 `all` 方法来返回**这个 post** 关联的全部评论。 其中 xxx_set 中的 xxx 为关联模型的类名（小写）。例如 `Post.objects.filter(category=cate)` 也可以等价写为 `cate.post_set.all()`。



# 其他问题

Django 允许我们在 models.Model 的子类里定义一个 Meta 的内部类，这个内部类通过指定一些属性来规定这个类该有的一些特性，例如在这里我们要指定 Post 的排序方式。首先看到 Post 的代码：



# 使用 Nginx 和 Gunicorn 部署 Django 博客

