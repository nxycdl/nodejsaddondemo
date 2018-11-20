var nxmi = require('nxmi');

const data = {
  yljgdm:'00000002',
  ip:'127.0.0.1',
  biztype:'J1',
  data:'<?xml version="1.0" encoding="GBK"?><DATA> <HEAD> <VER>01.01</VER> <APP>J2</APP> <WorkDate>20181116</WorkDate> <Reserve></Reserve> <ErrCode></ErrCode> <ErrDetail></ErrDetail> </HEAD> <MSG> <HEAD> <YLJGDM>00000002</YLJGDM><JYRQ>20181116000000</JYRQ><MZZYBZ>0</MZZYBZ><ZXBXBZ>0</ZXBXBZ><ZHCXBZ>1</ZHCXBZ><DKXXBZ>1</DKXXBZ><PWD>1</PWD></HEAD></MSG></DATA>'
}

const params = {
  'functionname':'bizbuss',
  'params':{
    'hid':data.yljgdm,
    'biztype':data.biztype,
    'ip':data.ip,
    'indata':data.data
  }
}

 console.log(nxmi)
console.log(nxmi.hello())
const outdata = (nxmi.invoke(JSON.stringify(params))); // 'hello world'
console.log(outdata);
var b = new Buffer.from(outdata, 'base64')
var s = b.toString();
console.log(s);