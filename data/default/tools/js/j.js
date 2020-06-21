//location this file relative djs.exe: "default/tools/js/j.js"
window.QtBrige = {
	/**
	 * {String} callback
	 * {String} stdout
	 * {String} stderr
	*/
	onFinish:function(callback, stdout, stderr) {
		if (window[callback] instanceof Function) {
			var re = new RegExp(Qt.getLineDelimeter(), 'mg');
			var out = stdout.replace(re, '\n'),
				stderr = stderr.replace(re, '\n');
			window[callback](out, stderr);
		}
	}
};

PHP.scandir = function(path) {
	var re = new RegExp(Qt.getLineDelimeter(), 'mg');
	var arr = PHP._scandir(path).split(re), i, b = [];
	for (i = 0; i < arr.length; i++) {
		b.push(arr[i].replace(path + '/', ''));
	}
	return b;
}

window.FILE_APPEND = 1;

/** @class localize */
window.addEventListener('load', __jqtCreateLocalizator, false);
function __jqtCreateLocalizator()
{
	var locale = document.getElementsByTagName('html')[0].getAttribute('lang'),
		filePath = Qt.appDir() + '/js/ru.json', loc;
	if (PHP.file_exists(filePath)) {
		try {
			loc = JSON.parse( PHP.file_get_contents(filePath) );
			//TODO здесь будет локализация
		} catch(e) {;}
		if (!loc) {
			//alert('Unable parse JSON data');
			return;
		}
		//Локализуем все value в input[type=button] и весь label.innerHTML
	} else {
		//alert(filePath);
	}
}
