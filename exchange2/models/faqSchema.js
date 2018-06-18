var mongoose = require('mongoose');
var faqSchema = mongoose.Schema({
    category: String,
    password: String,
    title: String,
    contents: String,
    deleted: {type: Boolean, default: false} // true면 삭제 된 경우임
});
module.exports =  mongoose.model('faqContents', faqSchema);