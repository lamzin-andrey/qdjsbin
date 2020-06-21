function initRb() {
	e('rbSelectFile').addEventListener('click', doOnSelectFile, true);
}
/**
 *  
*/
function doOnSelectFile() {
	var file = Qt.openFileDialog("Select bin file", "", "*.swf");
	var data = Qt.readFileAsBinaryString(file);
	e('rbCout').value = data;
}
