var mongoose = require('mongoose');
var boardSchema = mongoose.Schema({
    writer: String,
    password: String,
    title: String,
    contents: String,
    date: {type: Date, default: Date.now},
    updated: [{contents: String, date:{type: Date, default: Date.now}}],
    deleted: {type: Boolean, default: false} // true면 삭제 된 경우임
});
module.exports =  mongoose.model('BoardContents', boardSchema);