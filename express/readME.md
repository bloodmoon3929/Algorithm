# express
1. 어플리케이션
2. 미들웨어
3. 라우팅
4. 요청객체
5. 응답객체
6. CORS

## 어플리케이션
유효한 요청 handler, express의 인스턴스

## 미들웨어

## 라우팅
클라이언트가 url이나 method에 따라 특정 endpoint로 요청을 보낼 때, 어떻게 응답할지 정해두는 코드

라우팅을 설정하는 방법은 다음과 같다.
```js
app.METHOD(PATH,HANDLER)
```
* METHOD : HTPP 요청 메서드(get, post, put, delete)
* PATH : endpoint의 path
* HANDLER : 루트가 일치하다면 실행되는 함수

ex)

app.post('/login',(req,res,next)=>{
    next()
})

PATH : /login
HANDLER : (req,res, next)

next() 라는 argument로 다음 handler 실행
### 응용라우팅
* app.all()
어떤 메서드이든 상관없이 실행되는 메서드

* app.route()
같은 path를 가진 서로 다른 메소드를 묶어서 표현

ex)
```js
app.route('/book')
  .get((req, res) => {
    res.send('Get a random book')
  })
  .post((req, res) => {
    res.send('Add a book')
  })
  .put((req, res) => {
    res.send('Update the book')
  })
```

### 동적 PATH 생성
req의 파라미터의 값을 path에 넣을 수 있음

ex)
```js
app.get('/users/:userId/books/:bookId', (req, res) => {
  const {userId, bookId} = req.param
  res.send(userId + bookId)
})
```
해당 코드의 req 파라미터가 다음과 같다고 가정

req.param == {userId : 'minju', bookId : 'dictionary'}

그 경우 링크는 다음과 같음

http://localhost:3000/user/minju/book/dictionary

### 정적파일 제공
express으 내장 미들웨어를 이용하여, 정적인 파일을 제공가능하며 다음과 같다.
```js
app.use(express.static('public'))
```
public 폴더에 접근허용
```js
app.use('/static', express.static('public'))
// http://localhost:3000/static/images/test.jpeg
```
public 폴더의 images 폴더 내부의 test 사진을 띄움

다만 이는 상대 경로이기에 다른 폴더에서 실행이 에러를 유발함으로 path.join을 사용하여 절대경로를 지정해 주어야 함
```js
const path = require('path')
app.use('/static', express.static(path.join(__dirname, 'public')))
```

### express.router
app을 쪼개서 사용할 수 있도록 도와주는 핸들러이다. 미들웨어가 특정 라우터를 사용할 수 있도록 해주고, path에 따라 라우터를 쪼개서 관리할 수 있게 해준다.
```js
// color.js
import express from express
export const ColorRouter = express.Router()

ColorRouter.get('/red', HANDLER)
// http://localhost:3000/colors/red 로 접근 시 실행
...
```
```js
// app.js
import {ColorRouter} from './color'

// ...

app.use('/colors', colors)
```

## 요청객체

## 응답객체

## CORS
CORS(Cross-Origin Resource Sharing, 교차 출처 리소스 공유)

<img width="1408" alt="cors-url" src="https://github.com/bloodmoon3929/bloodmoon3929/assets/144004857/3e28d194-4c9f-485f-b24a-b6aab6aecd6c">

출처에 해당하는 부분이 위 사진의 Origin 부분이고,

SOP는 Origin이 하나라도 일치하지 않는다면, 리소스의 응답과 요청을 차단하는 정책이고,

CORS은 반대로 일치 하지 않더라도, 응답을 허용해 주는 정책이다.

![image](https://github.com/bloodmoon3929/bloodmoon3929/assets/144004857/bbf1d54d-377e-4afa-bcee-d5b36e8fdeaf)

해당 방식이 생긴 이유는 과거에는 프론트와 백엔드를 한번에 구축하여 같은 도메인 내에서 처리가 가능했으나, 현제는 클라이언트가 API를 요청하는 것이 당연해 지면서 출처가 다르더라도 요청과 응답을 받을 수 있게 서버에 리소스 호출이 허가된 출처를 명시하는 방식인 CORS 방식이 생겨남


### CORS 에러 대응하기
* 응답헤더 설정하기
서버에서 Access-Control-Allow-Origin 헤더를 설정하여 요청을 수락할 출처를 명시적으로 지정할 수 있다
```js
'Access-Control-Allow-Origin': <origin> | *
```

* 프록시 서버 사용하기
웹 애플리케이션이 리소스를 직접적으로 요청하는 대신, 프록시 서버를 사용하여 웹 애플리케이션에서 리소스로의 요청을 전달하는 방법도 있다. 이 방법을 사용하면, 웹 애플리케이션이 리소스와 동일한 출처에서 요청을 보내는 것처럼 보이므로 CORS 에러를 방지할 수 있다.

예를 들어, http://example.com라는 주소의 웹 애플리케이션이 http://api.example.com라는 리소스에서 데이터를 요청하는 상황을 가정

 웹 애플리케이션은 직접적으로 리소스에 요청하는 대신, http://example-proxy.com라는 프록시 서버에 요청을 보냄
 
 그러면 프록시 서버가 http://api.example.com으로 요청을 전달하고, 응답을 다시 웹 애플리케이션에 반환
 
이렇게 하면 요청이 http://example-proxy.com보내진 것처럼 보이므로, CORS 에러를 피할 수 있다

### express에서의 CORS
```
$ npm install cors
```
우선 CORS를 설치한다.

1. 모든 CORS 요청 활성화

```js
var express = require('express')
var cors = require('cors')
var app = express()

app.use(cors())

app.get('/products/:id', function (req, res, next) {
  res.json({msg: '모든 출처에 대하여 CORS 허용'})
})

app.listen(80, function () {
  console.log('CORS-enabled web server listening on port 80')
})
```

2. 단일 route에 대해 CORS 활성화

```js
var express = require('express')
var cors = require('cors')
var app = express()

app.get('/products/:id', cors(), function (req, res, next) {
  res.json({msg: '단일 라우트에 대하여 CORS 허용'})
})

app.listen(80, function () {
  console.log('CORS-enabled web server listening on port 80')
})
```

3. CORS 구성

```js
var express = require('express')
var cors = require('cors')
var app = express()

var corsOptions = {
  origin: 'http://example.com',
  optionsSuccessStatus: 200 
}

app.get('/products/:id', cors(corsOptions), function (req, res, next) {
  res.json({msg: 'example.com 출처에 대해서만 CORS 허용'})
})

app.listen(80, function () {
  console.log('CORS-enabled web server listening on port 80')
})
```
추가로 기본 구성은 다음과 같습니다.
```js
{
  "origin": "*",
  "methods": "GET,HEAD,PUT,PATCH,POST,DELETE",
  "preflightContinue": false,
  "optionsSuccessStatus": 204
}
```


4. 동적 출처을 사용하여 CORS 구성

```js
var express = require('express')
var cors = require('cors')
var app = express()

var corsOptions = {
  origin: function (origin, callback) {
    // db.loadOrigins is an example call to load
    // a list of origins from a backing database
    db.loadOrigins(function (error, origins) {
      callback(error, origins)
    })
  }
}

app.get('/products/:id', cors(corsOptions), function (req, res, next) {
  res.json({msg: 'This is CORS-enabled for an allowed domain.'})
})

app.listen(80, function () {
  console.log('CORS-enabled web server listening on port 80')
})
```

5. 사전허용
```js
var express = require('express')
var cors = require('cors')
var app = express()

app.options('/products/:id', cors()) // enable pre-flight request for DELETE request
app.del('/products/:id', cors(), function (req, res, next) {
  res.json({msg: 'This is CORS-enabled for all origins!'})
})

app.listen(80, function () {
  console.log('CORS-enabled web server listening on port 80')
})
```
```js
app.options('*', cors())
```

6. 비동기식으로 구성하기
```js
var express = require('express')
var cors = require('cors')
var app = express()

var allowlist = ['http://example1.com', 'http://example2.com']
var corsOptionsDelegate = function (req, callback) {
  var corsOptions;
  if (allowlist.indexOf(req.header('Origin')) !== -1) {
    corsOptions = { origin: true } // reflect (enable) the requested origin in the CORS response
  } else {
    corsOptions = { origin: false } // disable CORS for this request
  }
  callback(null, corsOptions) // callback expects two parameters: error and options
}

app.get('/products/:id', cors(corsOptionsDelegate), function (req, res, next) {
  res.json({msg: 'This is CORS-enabled for an allowed domain.'})
})

app.listen(80, function () {
  console.log('CORS-enabled web server listening on port 80')
})
```

origin: Access-Control-Allow-Origin CORS 헤더를 구성합니다. 가능한 값:
Boolean- 에서 정의한 대로 요청 출처를 반영하도록 origin설정 하거나 CORS를 비활성화하려면 로 설정합니다. truereq.header('Origin')false


String- origin특정 출처로 설정됩니다. 예를 들어 "http://example.com"의 요청만 허용되도록 설정하면 "http://example.com"허용됩니다.


RegExp- origin요청 출처를 테스트하는 데 사용될 정규식 패턴으로 설정합니다. 일치하는 경우 요청 출처가 반영됩니다. 예를 들어 패턴은 /example\.com$/"example.com"으로 끝나는 원본에서 오는 모든 요청을 반영합니다.


Array- origin유효한 출처의 배열로 설정됩니다. 각 원점은 a String또는 a 일 수 있습니다 RegExp. 예를 들어 ["http://example1.com", /\.example2\.com$/]"http://example1.com" 또는 "example2.com" 하위 도메인의 모든 요청을 수락합니다.


Function- origin일부 사용자 정의 논리를 구현하는 함수로 설정합니다. 이 함수는 요청 출처를 첫 번째 매개변수로 사용하고 콜백( 이라고 함 callback(err, origin), 여기서 는 옵션 origin의 함수 값이 아님 origin)을 두 번째 매개변수로 사용합니다.


methods: Access-Control-Allow-Methods CORS 헤더를 구성합니다. 쉼표로 구분된 문자열(예: 'GET,PUT,POST') 또는 배열(예: ['GET', 'PUT', 'POST'])이 필요합니다.


allowedHeaders: Access-Control-Allow-Headers CORS 헤더를 구성합니다. 쉼표로 구분된 문자열(예: 'Content-Type,Authorization') 또는 배열(예: ['Content-Type', 'Authorization'])이 필요합니다. 지정하지 않으면 기본적으로 요청의 Access-Control-Request-Headers 헤더에 지정된 헤더를 반영합니다.


exposedHeaders: Access-Control-Expose-Headers CORS 헤더를 구성합니다. 쉼표로 구분된 문자열(예: 'Content-Range,X-Content-Range') 또는 배열(예: ['Content-Range', 'X-Content-Range'])이 필요합니다. 지정하지 않으면 사용자 정의 헤더가 노출되지 않습니다.


credentials: Access-Control-Allow-Credentials CORS 헤더를 구성합니다. 헤더를 전달하려면 로 설정하고 true, 그렇지 않으면 생략됩니다.


maxAge: Access-Control-Max-Age CORS 헤더를 구성합니다. 헤더를 전달하려면 정수로 설정하고, 그렇지 않으면 생략됩니다.


preflightContinue: CORS 실행 전 응답을 다음 핸들러에 전달합니다.


optionsSuccessStatusOPTIONS: 일부 레거시 브라우저(IE11, 다양한 SmartTV)가 중단되므로 성공적인 요청에 사용할 상태 코드를 제공합니다 204.


## 크롤링
해당 주소 참고 : https://velog.io/@nemo/movie-search-app-2
### 기본 세팅
* axios: 웹 페이지의 HTML을 가져옴
* cheerio: 가져온 HTML에서 필요한 정보를 추출(파싱)

### 예제코드
```js
// 설치한 axios와 cheerio 모듈을 가져온다.
const cheerio = require("cheerio");
const axios = require("axios");

// axios로 HTML을 가져오는 함수
const getHTML = async () => {
  try {
    return await axios.get('https://movie.naver.com/movie/sdb/rank/rmovie.naver')
  } catch (error) {
    console.log(error);
  }
}

// 파싱
const parsing = async () => {
  // 위에서 추출한 HTML 전체 가져오기
  const html = await getHTML();
  // JQuery처럼 사용하기 위해 '$'에 cheerio를 로드한다.
  const $ = cheerio.load(html.data);
  
  // 개발자 모드에서 확인해보면
  // .list_ranking 아래 tr들이 있고 그 안에 하나씩 타이틀 존재
  // 반복문을 돌릴 수 있어야 하니 병렬로 있는 요소까지만 찾는다.
  const $trs = $("#old_content > .list_ranking > tbody > tr");
 
  // 파싱한 데이터를 담을 배열
  let dataArr = [];

  // 찾은 tr 개수 만큼 반복문을 돌린다.
  $trs.each((idx, node) => {
    const title = $(node).find(".tit3 a").text();
    const link = $(node).find(".tit3 a").attr("href");

    // 빈 값 리턴
    if (title === "") {
      return;
    }

    // 오브젝트 형식으로 배열에 담기
    dataArr.push({
      title: title,
      link: link
    });
  });

  console.log(dataArr)
}
parsing()
module.exports = parsing;
```

```js
const express = require("express");
const app = express();
const port = process.env.PORT || 5000;
...
// parsing 모듈 import
const parsing = require('./fetching.js');

...

// api/rank로 get 요청이 들어오면 
// parsing() 실행해서 요청 결괏값 client로 내보내기
app.get('/api/rank', (req, res) => {
  parsing().then(response => res.send(response))
})

...

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});

```

참고자료

https://github.com/wwlee94/everytime-timetable-crawling

https://github.com/pdjdev/uTable

우리랑 다른 방식의 공통 공강 찾기(응용해서 시간표 등록 가능할 듯?)

https://github.com/ecsimsw/gap-between-classes

https://github.com/juijeong8324/MyEveryMap

https://github.com/shin0park/ajou-timetable-back-end

https://github.com/hyeonseongkang/Schedule-Android

https://blog.naver.com/PostView.nhn?blogId=kkj6369&logNo=221437993432