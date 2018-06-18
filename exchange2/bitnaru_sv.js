const port = 4000;
const portssl = 443;
var express = require('express');
var app = express();
var path = require("path");



app.use(express.static(__dirname + '/'));

var index = require('./routes/content');

/* VIEW ENGINE SETUP */
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use('/', index);



var bodyParser = require('body-parser');
var axios = require('axios');

app.use(bodyParser.json());

app.post("/verification", (request, response) => {
  const { imp_uid } = request.body; // request의 body에서 imp_uid 추출
  aa();

  async function aa() {
    try {
        // 인증 토큰 발급 받기
        const getToken = await axios({
            url: "https://api.iamport.kr/users/getToken",
            method: "post", // POST method
            headers: { "Content-Type": "application/json" }, // "Content-Type": "application/json"
            data: {
                imp_key: "3277016797574556", // REST API키
                imp_secret: "gxILAKyW2jE6ujRs1oerUL2RlG7vmKjDh2oSMXPPgtVLNMeObsf6ehXzY45lPoY6rnZelO4Ci0n5MCUY" // REST API Secret
            }
        });
        const { access_token } = getToken.data.response; // 인증 토큰

        console.log(access_token);

        // imp_uid로 인증 정보 조회
        const getCertifications = await axios({
            url: `https://api.iamport.kr/verification/${imp_uid}`, // imp_uid 전달
            method: "get", // GET method
            headers: { "Authorization": access_token } // 인증 토큰 Authorization header에 추가
        });
        const certificationsInfo = getCertifications.data.response; // 조회한 인증 정보

    } catch(e) {
        console.error(e);
    }
  }
});



/* CONNECT DB */
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/board');

var db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function() {
  console.log("connected");
});


/* 404 ERROR */
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});
// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
  app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
      message: err.message,
      error: err
    });
  });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
  res.status(err.status || 500);
  res.render('error', {
    message: err.message,
    error: {}
  });
});



/* 글쓰기 */

/* WEBSOCKET CHATTING */
var http = require('http').Server(app);
var io = require('socket.io')(http);


var idBlock = mongoose.Schema({
    accountId : 'string',
    block: 'string'
});
var idBlock = mongoose.model('Schema', idBlock);

var newidBlock = new idBlock({accountId:'', block:'true'});
newidBlock.save(function(error, data){ // 데이터베이스 집어넣기
    if(error){
        console.log(error);
    }else{
        console.log('Saved!')
    }
});


var bankContents = require('./models/bankSchema');
var chatContents = require('./models/chatSchema');
var userContents = require('./models/userSchema');

io.on('connection', function(socket){
    /* 게시판 글 쓰기 버튼 노출 체크 */
    socket.on('levChk', function(lev){
      if (lev != undefined) {
          lev = lev;
      } else {
          lev = 0;
      }
      if (lev == 10) {
          io.emit('levChk', lev);
      }
    });


    /* 글쓰기, 수정하기 level 체크 */
    socket.on('writeChk', function(level){
      if (level != undefined || level != null) {
          level = level;
      } else {
          level = 0;
      }
      if (level != 10) {
          io.emit('writeChk', level);
      }
    })



    socket.on('idBlock', function(id){
      console.log(id);
    });

    
    socket.on('chat message', function(name,msg,accountId){
      // chatContents.findOne({userId:accountId}, function(err, rawContent){
      //     if(err) throw err;
      //     var banId = rawContent.userId;
      //     if (banId == accountId) { // account Id 체크해서 채팅 금지 시키기
      //       io.to(socket.id).emit('idChk', name,accountId)
      //       return
      //     } else {
      //   }
      // });      
        // io.emit('chat message', name,msg,accountId);
    });


    // socket통신으로 은행정보 DB 가져오기
    socket.on('bankId', function(idVal){
      bankContents.findOne({accountId:idVal}, function(err, rawContent){
          if(err) throw err;
          io.emit('bankId', rawContent);
      });
    })

    socket.on('verifit', function(idVal){
      userContents.findOne({accountId:idVal}, function(err, rawContent){
          if(err) throw err;
          io.emit('verifit', rawContent);
      });
    })


    socket.on('bankInfo', function(acId){
      bankContents.findOne({accountId:acId}, function(err, rawContent){
          if(err) throw err;
          console.log(rawContent);
          io.emit('bankInfo', rawContent);
      });
    })
});


/* WEB SERVER START */
http.listen(port, function(){
   console.log('server on');
});
