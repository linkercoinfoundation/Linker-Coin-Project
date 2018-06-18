var mongoose = require('mongoose');
var bankSchema = mongoose.Schema({
    accountId: String,
    bankName: String,
    bankAddr: String,
    updated: [{contents: String, date:{type: Date, default: Date.now}}]
});
module.exports =  mongoose.model('bankInfo', bankSchema);