var express = require('express');
var BoardContents = require('../models/boardsSchema'); //db를 사용하기 위한 변수
var faqContents = require('../models/faqSchema');
var bankContents = require('../models/bankSchema');
var chatContents = require('../models/chatSchema');
var userContents = require('../models/userSchema');
var fs = require('fs');
var multer = require('multer'); // 파일 저장을 위한  multer
// var upload = multer({dest:'./tmp/'}); // multer 경로 설정, 파일이 업로드 되면 먼저 임시 폴더로 가서 저장됨
var path = require('path');
var upload = multer({
    limits: { fileSize: 5 * 1024 * 1024 },
    storage: multer.diskStorage({
        destination: function (req, file, cb) {
          cb(null, './tmp/');
        },
        filename: function (req, file, cb) {
          cb(null, new Date().valueOf() + path.extname(file.originalname));
        }
    }),
});

var router = express.Router();

router.get('/', function(req, res) {
  res.render('index', { title: 'index' });
});
router.get('/index.html', function(req, res) {
  res.render('index', { title: 'index' });
});
router.get('/exchange', function(req, res) {
  res.render('exchange', { title: 'exchange' });
});
router.get('/exchange_test', function(req, res) {
  res.render('exchange_test', { title: 'exchange_test' });
});
router.get('/dashboard', function(req, res) {
  res.render('dashboard', { title: 'dashboard' });
});
router.get('/termsOfUse', function(req, res) {
  res.render('termsOfUse', { title: 'termsOfUse' });
});
router.get('/privacyPolicy', function(req, res) {
  res.render('privacyPolicy', { title: 'privacyPolicy' });
});
router.get('/myPage', function(req, res) {
    res.render('myPage', { title: 'myPage' });
});
router.get('/wallet', function(req, res) {
    res.render('wallet', { title: 'wallet' });
});
router.get('/transactionDetails', function(req, res) {
    res.render('transactionDetails', { title: 'transactionDetails'});
});
router.get('/feeInformation', function(req, res) {
    res.render('feeInformation', { title: 'feeInformation'});
});
router.get('/informationUse', function(req, res) {
    res.render('informationUse', { title: 'informationUse'});
});

router.get('/kyc', function(req, res) {
    res.render('kyc', { title: 'kyc'});
});

router.get('/verification_test', function(req, res) {
    res.render('verification_test');
});
router.get('/chatban', function(req, res) {
    res.render('chatban');
});

router.get('/test', function(req, res) {
    res.render('test');
});


router.post('/test', upload.array('UploadFile'),function(req, res){ 

    var accountId = req.body.accountId;
    var fullname = req.body.fullname;
    var birthday = req.body.birthday;
    var sex = req.body.sex;
    var nation = req.body.nation;
    var telComCd = req.body.telComCd;
    var telNo = req.body.telNo;

    addUserInfo(accountId, fullname, birthday, sex, nation, telComCd, telNo);

    res.send('<script type="text/javascript">window.close();</script>');
});

function addUserInfo(accountId, fullname, birthday, sex, nation, telComCd, telNo) {
    var newUserCont = new userContents;
    newUserCont.accountId = accountId;
    newUserCont.fullname = fullname;
    newUserCont.birthday = birthday;
    newUserCont.sex = sex;
    newUserCont.nation = nation;
    newUserCont.telComCd = telComCd;
    newUserCont.telNo = telNo;

    newUserCont.save(function (err) {
        if (err) throw err;
        userContents.findOne({_id: newUserCont._id}, {_id: 1}, function (err, newBoardId) {
            if (err) throw err;
        });
    });
}




router.get('/security', function(req, res) {
    res.render('security', {title: 'security', content: false});

});

/* 은행정보 입력*/
router.post('/security', upload.array('UploadFile'),function(req, res){ 
    var mode = req.query.mode;

    var accountId = req.body.addAccountId;
    var bankName = req.body.addBankName;
    var bankAddr = req.body.addBankAddr;

    if(mode == 'add') {
        addBankInfo(accountId, bankName, bankAddr);
        res.redirect('/security');
    }
});


function addBankInfo(accountId, bankName, bankAddr){
    var newBankInfo = new bankContents;
    newBankInfo.accountId = accountId;
    newBankInfo.bankName = bankName;
    newBankInfo.bankAddr = bankAddr;

    newBankInfo.save(function (err) {
        if (err) throw err;
        faqContents.findOne({_id: newBankInfo._id}, {_id: 1}, function (err, newBoardId) {
            if (err) throw err;
        });
    });
}

router.post('/chatban', upload.array('UploadFile'), function(req, res) {
    var mode = req.query.mode;

    var accountId = req.body.banAccountId;
    if (mode == 'ban') {
        chatIdBan(accountId);
        res.redirect('/chatban');
    }
})

function chatIdBan(accountId) {
    var banlist = new chatContents;
    banlist.userId = accountId;

    banlist.save(function (err) {
        if (err) throw err;
        chatContents.findOne({_id: banlist._id}, {_id: 1}, function (err, newBoardId) {
            if (err) throw err;
        });
    })
}


/* 메일전송 */
router.post('/kyc', upload.fields([{name: 'identification'}, {name:'IdentityAuthentication'}]), function(req, res) {
    var nodemailer = require('nodemailer');
    var transporter = nodemailer.createTransport({
        service:'gmail',
        auth: {
            user : 'yong880211@gmail.com',
            pass : 'dltjd9700!'
        }
    });
    var mode = req.query.mode;
    var accountId = req.body.accountId;
    var email = req.body.email;
    var thumb01 = req.files.identification;
    var thumb02 = req.files.IdentityAuthentication;

    if (mode == "send") {
        var mailOption = {
            from : email,
            to : 'service@bitnaru.com',
            subject : accountId+'님 KYC인증 메일',
            text : "회원 번호:"+accountId+" 이메일주소:"+email+" 신원인증 사진",
            attachments:[
                {
                    fileName: 'thumb',
                    path: thumb01[0].path
                },
                {
                    fileName: 'thumb',
                    path: thumb02[0].path
                },

            ]
        };
        transporter.sendMail(mailOption, function(err, info) {
            if ( err ) {
                console.error('Send Mail error : ', err);
                res.redirect('/kyc');
            }
            else {
                fs.unlink(thumb01[0].path, function (err) {
                    if (err)
                    throw err;
                });
                fs.unlink(thumb02[0].path, function (err) {
                    if (err)
                    throw err;
                });
                res.send('<script type="text/javascript">alert("전송완료");history.back();</script>');
            }
        });
        transporter.close();
    }
})







router.get('/notice', function(req,res){

    var page = req.query.page;
    if(page == null) {page = 1;}

    var skipSize = (page-1)*10;
    var limitSize = 10;
    var pageNum = 1;


    BoardContents.count({deleted:false},function(err, totalCount){
        if(err) throw err;

        pageNum = Math.ceil(totalCount/limitSize);
        BoardContents.find({deleted:false}).sort({date:-1}).skip(skipSize).limit(limitSize).exec(function(err, pageContents) {
            if(err) throw err;
            res.render('board', {title: "Board", contents: pageContents, pagination: pageNum, searchWord: ''});
        });
    });
});

router.get('/write', function(req,res){
	res.render('write', { title: 'write' });
});

router.get('/modify', function(req,res){
    var contentId = req.query.id;

    BoardContents.findOne({_id:contentId}, function(err, rawContent){
        if(err) throw err;

        rawContent.save(function(err){
            if(err) throw err;

            res.render('modify',{title: "modify", content:rawContent});
        });
    })
});

router.get('/category', function(req, res){
    // 글 검색하는 부분
    var search_word = req.query.ca_name;
    var searchCondition = {$regex:search_word};

    var page = req.query.page;
    if(page == null) {page = 1;}
    var skipSize = (page-1)*10;
    var limitSize = 10;
    var pageNum = 1;

    BoardContents.count({deleted:false, $or:[{writer:searchCondition}]},function(err, searchCount){
        if(err) throw err;
        pageNum = Math.ceil(searchCount/limitSize);

        BoardContents.find({deleted:false, $or:[{writer:searchCondition}]}).sort({date:-1}).skip(skipSize).limit(limitSize).exec(function(err, searchContents){
            if(err) throw err;

            res.render('board', {title: "Board", contents: searchContents, pagination: pageNum, searchWord: search_word});
        });
    });
});

router.get('/search', function(req, res){
    // 글 검색하는 부분
    var search_word = req.query.searchWord;
    var searchCondition = {$regex:search_word};

    var page = req.query.page;
    if(page == null) {page = 1;}
    var skipSize = (page-1)*10;
    var limitSize = 10;
    var pageNum = 1;

    BoardContents.count({deleted:false, $or:[{title:searchCondition},{contents:searchCondition}]},function(err, searchCount){
        if(err) throw err;
        pageNum = Math.ceil(searchCount/limitSize);

        BoardContents.find({deleted:false, $or:[{title:searchCondition},{contents:searchCondition}]}).sort({date:-1}).skip(skipSize).limit(limitSize).exec(function(err, searchContents){
            if(err) throw err;

            res.render('board', {title: "Board", contents: searchContents, pagination: pageNum, searchWord: search_word});
        });
    });
});


router.post('/notice', upload.array('UploadFile'),function(req, res){
    //field name은 form의 input file의 name과 같아야함
    // 글 작성하고 submit하게 되면 저장이 되는 부분
    // 글 수정하고 submit하면 수정된 결과가 저장되는 부분
    var mode = req.query.mode;



    var addNewTitle = req.body.addContentSubject;
    var addNewWriter = req.body.addContentWriter;
    var addNewPassword = req.body.addContentPassword;
    var addNewContent = req.body.addContents;

    var modId = req.body.modId;
    var modTitle = req.body.modContentSubject;
    var modContent = req.body.modContents;
    var modWriter = req.body.modContentWriter;

    if(mode == 'add') {
        addBoard(addNewTitle, addNewWriter, addNewContent, addNewPassword);
        res.redirect('/notice');
    } else if (mode == 'modify') {
        modBoard(modId, modTitle, modContent, modWriter);
        res.redirect('/notice');
    }
});

router.get('/download/:path', function(req, res){
    // file download

    var path = req.params.path;
    res.download('./upload/'+path, path);
    console.log(path);
});

router.get('/delete', function(req, res) {
    // 삭제하는 부분

    var contentId = req.query.id;

    BoardContents.update({_id:contentId}, {$set:{deleted:true}}, function(err){
        if(err) throw err;
        res.redirect('/notice');
    });
});

router.get('/view', function(req, res){

    var contentId = req.query.id;

    BoardContents.findOne({_id:contentId}, function(err, rawContent){
        if(err) throw err;

        rawContent.save(function(err){
            if(err) throw err;

            res.render('boardDetail',{title: "Board", content:rawContent});
        });
    })
});

router.get('/password', function(req, res){
    // 글 비밀번호 찾아오기
    var id = req.query.id;

    BoardContents.findOne({_id: id}, function(err, rawContents){
       res.send(rawContents.password);
    });
});











router.get('/faqWrite', function(req,res){
    res.render('faqWrite', { title: 'write' });
});

router.get('/faqCategory', function(req, res){
    // 글 검색하는 부분
    var search_word = req.query.ca_name;
    var searchCondition = {$regex:search_word};

    var page = req.query.page;
    if(page == null) {page = 1;}
    var skipSize = (page-1)*10;
    var limitSize = 10;
    var pageNum = 1;

    faqContents.count({deleted:false, $or:[{category:searchCondition}]},function(err, searchCount){
        if(err) throw err;
        pageNum = Math.ceil(searchCount/limitSize);

        faqContents.find({deleted:false, $or:[{category:searchCondition}]}).sort({date:-1}).skip(skipSize).limit(limitSize).exec(function(err, searchContents){
            if(err) throw err;

            res.render('faq', {title: "Board", contents: searchContents, pagination: pageNum, searchWord: search_word});
        });
    });
});

router.get('/faq', function(req,res){
    // 처음 index로 접속 했을시 나오는 부분
    // db에서 게시글 리스트 가져와서 출력
    // pagination 추가 -> 11/17
    // page는 1-5까지 보여줌 -> db에서 총 갯수 잡아와서 10으로 나눠서 올림해야함
    // 한페이지에 10개의 게시글: limit: 10, skip: (page-1)*10 이면 될 듯
    // page number는 param으로 받아오기 가장 처음엔 param 없으니까 그땐 자동 1로 설정

    var page = req.query.page;
    if(page == null) {page = 1;}

    var skipSize = (page-1)*10;
    var limitSize = 10;
    var pageNum = 1;


    faqContents.count({deleted:false},function(err, totalCount){
       // db에서 날짜 순으로 데이터들을 가져옴
        if(err) throw err;

        pageNum = Math.ceil(totalCount/limitSize);
        faqContents.find({deleted:false}).sort({date:-1}).skip(skipSize).limit(limitSize).exec(function(err, pageContents) {
            if(err) throw err;
            res.render('faq', {title: "FAQ", contents: pageContents, pagination: pageNum, searchWord: ''});
        });
    });
});

router.post('/faq', upload.array('UploadFile'),function(req, res){
    //field name은 form의 input file의 name과 같아야함
    // 글 작성하고 submit하게 되면 저장이 되는 부분
    // 글 수정하고 submit하면 수정된 결과가 저장되는 부분
    var mode = req.query.mode;

    var faqTitle = req.body.addFaqSubject;
    var faqCategory = req.body.addFaqCategory;
    var faqPassword = req.body.addFaqPassword;
    var faqContents = req.body.addFaqContents;

    var modId = req.body.modFaqId;
    var modTitle = req.body.modFaqSubject;
    var modContent = req.body.modFaqContents;
    var modCategory = req.body.modFaqCategory;

    if(mode == 'add') {
        addFaq(faqTitle, faqCategory, faqContents, faqPassword);
        res.redirect('/faq');
    } else if (mode == 'modify') {
        modfaq(modId, modTitle, modContent, modCategory);
        res.redirect('/faq');
    }
});


router.get('/faqModify', function(req,res){
    var contentId = req.query.id;

    faqContents.findOne({_id:contentId}, function(err, rawContent){
        if(err) throw err;
        rawContent.save(function(err){
            if(err) throw err;
            res.render('faqModify',{title: "Board", content:rawContent});
        });
    })
});


router.get('/faqDelete', function(req, res) {

    var contentId = req.query.id;

    faqContents.update({_id:contentId}, {$set:{deleted:true}}, function(err){
        if(err) throw err;
        res.redirect('/faq');
    });
});

router.get('/faqPassword', function(req, res){
    var id = req.query.id;

    faqContents.findOne({_id: id}, function(err, rawContents){
       res.send(rawContents.password);
    });
});


router.get('/faqSearch', function(req, res){
    // 글 검색하는 부분
    var search_word = req.query.searchWord;
    var searchCondition = {$regex:search_word};

    var page = req.query.page;
    if(page == null) {page = 1;}
    var skipSize = (page-1)*10;
    var limitSize = 10;
    var pageNum = 1;

    faqContents.count({deleted:false, $or:[{title:searchCondition},{contents:searchCondition}]},function(err, searchCount){
        if(err) throw err;
        pageNum = Math.ceil(searchCount/limitSize);

        faqContents.find({deleted:false, $or:[{title:searchCondition},{contents:searchCondition}]}).sort({date:-1}).skip(skipSize).limit(limitSize).exec(function(err, searchContents){
            if(err) throw err;

            res.render('faq', {title: "faq", contents: searchContents, pagination: pageNum, searchWord: search_word});
        });
    });
});

module.exports = router;



function addBoard(title, writer, content, password, upFile){
    var newContent = content.replace(/\r\n/gi, "\\r\\n");

    var newBoardContents = new BoardContents;
    newBoardContents.writer = writer;
    newBoardContents.title = title;
    newBoardContents.contents = newContent;
    newBoardContents.password = password;

    newBoardContents.save(function (err) {
        if (err) throw err;
        BoardContents.findOne({_id: newBoardContents._id}, {_id: 1}, function (err, newBoardId) {
            if (err) throw err;

            if (upFile != null) {
                var renaming = renameUploadFile(newBoardId.id, upFile);

                for (var i = 0; i < upFile.length; i++) {
                    fs.rename(renaming.tmpname[i], renaming.fsname[i], function (err) {
                        if (err) {
                            console.log(err);
                            return;
                        }
                    });
                }

                for (var i = 0; i < upFile.length; i++) {
                    BoardContents.update({_id: newBoardId.id}, {$push: {fileUp: renaming.fullname[i]}}, function (err) {
                        if (err) throw err;
                    });
                }
            }
        });
    });
}


function modBoard(id, title, content, writer) {
    var modContent = content.replace(/\r\n/gi, "\\r\\n");

    BoardContents.findOne({_id:id}, function(err, originContent){
        if(err) throw err;
        originContent.updated.push({title: originContent.title, contents:originContent.contents});
        originContent.save(function(err){
            if(err) throw err;
        });
    });

    BoardContents.update({_id:id}, {$set: {title: title, contents: modContent, writer: writer }}, function(err) {
        if(err) throw err;
    });
}

function addComment(id, writer, comment) {
    BoardContents.findOne({_id: id}, function(err, rawContent){
        if(err) throw err;

        rawContent.comments.unshift({name:writer, memo: comment});
        rawContent.save(function(err){
            if(err) throw err;
        });
    });
}
function getFileDate(date) {
    var year = date.getFullYear();
    var month = date.getMonth()+1;
    var day = date.getDate();

    var fullDate = year+""+month+""+day;

    return fullDate
}

function renameUploadFile(itemId,upFile){
    // 업로드 할때 리네이밍 하는 곳!
    var renameForUpload = {};
    var newFile = upFile; // 새로 들어 온 파일
    var tmpPath = [];
    var tmpType = [];
    var index = [];
    var rename = [];
    var fileName = [];
    var fullName = []; // 다운로드 시 보여줄 이름 필요하니까 원래 이름까지 같이 저장하자!
    var fsName = [];

    for (var i = 0; i < newFile.length; i++) {
        tmpPath[i] = newFile[i].path;
        tmpType[i] = newFile[i].mimetype.split('/')[1]; // 확장자 저장해주려고!
        index[i] = tmpPath[i].split('/').length;
        rename[i] = tmpPath[i].split('/')[index[i] - 1];
        fileName [i] = itemId + "_" + getFileDate(new Date()) + "_" + rename[i] + "." + tmpType[i]; // 파일 확장자 명까지 같이 가는 이름 "글아이디_날짜_파일명.확장자"
        fullName [i] = fileName[i] + ":" + newFile[i].originalname.split('.')[0]; // 원래 이름까지 같이 가는 이름 "글아이디_날짜_파일명.확장자:보여줄 이름"
        fsName [i] = getDirname(1)+"upload/"+fileName[i]; // fs.rename 용 이름 "./upload/글아이디_날짜_파일명.확장자"
    }

    renameForUpload.tmpname = tmpPath;
    renameForUpload.filename = fileName;
    renameForUpload.fullname = fullName;
    renameForUpload.fsname = fsName;

    return renameForUpload;
}

function getDirname(num){
    //원하는 상위폴더까지 리턴해줌. 0은 현재 위치까지, 1은 그 상위.. 이런 식으로
    // 리네임과, 파일의 경로를 따오기 위해 필요함.

    var order = num;
    var dirname = __dirname.split('/');
    var result = '';

    for(var i=0;i<dirname.length-order;i++){
        result += dirname[i] + '/';
    }

    return result;
}

function isSaved(upFile) {
    // 파일 저장 여부 확인해서 제대로 저장되면 디비에 저장되는 방식

    var savedFile = upFile;
    var count = 0;

    if(savedFile != null) { // 파일 존재시 -> tmp폴더에 파일 저장여부 확인 -> 있으면 저장, 없으면 에러메시지
        for (var i = 0; i < savedFile.length; i++) {
            if(fs.statSync(getDirname(1) + savedFile[i].path).isFile()){ //fs 모듈을 사용해서 파일의 존재 여부를 확인한다.
                count ++; // true인 결과 갯수 세서
            };

        }
        if(count == savedFile.length){  //올린 파일 갯수랑 같으면 패스
            return true;
        }else{
            return false;
        }
    }else{ // 파일이 처음부터 없는 경우
        return true;
    }
}





function addFaq(title, category, content, password){
    var newContent = content.replace(/\r\n/gi, "\\r\\n");

    var newFaqContents = new faqContents;
    newFaqContents.category = category;
    newFaqContents.title = title;
    newFaqContents.contents = newContent;
    newFaqContents.password = password;

    newFaqContents.save(function (err) {
        if (err) throw err;
        faqContents.findOne({_id: newFaqContents._id}, {_id: 1}, function (err, newBoardId) {
            if (err) throw err;
        });
    });
}

function modfaq(id, title, content, category) {
    var modContent = content.replace(/\r\n/gi, "\\r\\n");

    faqContents.findOne({_id:id}, function(err, originContent){
        if(err) throw err;
        originContent.updated.push({title: originContent.title, contents:originContent.contents});
        originContent.save(function(err){
            if(err) throw err;
        });
    });

    faqContents.update({_id:id}, {$set: {title: title, contents: modContent, category: category }}, function(err) {
        if(err) throw err;
    });
}