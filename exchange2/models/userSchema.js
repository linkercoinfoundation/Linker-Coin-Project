var mongoose = require('mongoose');
var userSchema = mongoose.Schema({
	accountId: String,
    fullname: String,
    birthday: String,
    sex: String,
    nation: String,
    telComCd: String,
    telNo: String,
    updated: [{contents: String, date:{type: Date, default: Date.now}}],
    deleted: {type: Boolean, default: false} // true면 삭제 된 경우임
});
module.exports =  mongoose.model('userContents', userSchema);