/**
 * @file crazycube.js
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief js for crazycube system webserver
 * @version 1.0
 * @date 2022-12-16
 *
 * @copyright Copyright (c) 2022
 *
 */
//------------------ ALL ------------------
//加载 数据
$(function() {
    initKeyboardOption();
    loadSysInfos();
});

function showToast(msg, duration) {
    duration = isNaN(duration) ? 2000 : duration;
    var m = document.createElement('div');
    m.innerHTML = msg;
    m.style.cssText = "width:60%; min-width:180px; background:#000; opacity:0.6; height:auto;min-height: 30px; color:#fff; line-height:30px; text-align:center; border-radius:4px; position:fixed; top:60%; left:20%; z-index:999999;";
    document.body.appendChild(m);
    setTimeout(function() {
        var d = 0.5;
        m.style.webkitTransition = '-webkit-transform ' + d + 's ease-in, opacity ' + d + 's ease-in';
        m.style.opacity = '0';
        setTimeout(function() {
            document.body.removeChild(m)
        }, d * 1000);
    }, duration);
}

// 检查更新数据是否成功
var checkUpdateResult = function(result, statue) {
    if (statue == "success")
        showToast("更新成功！");
    else
        showToast("更新失败，请重试!");
}

// 获取数据
var getData = function(url, successCallback) {
    $.ajax({
        async: true,
        cache: false,
        dataType: 'json',
        url: url,
        type: 'get',
        success: successCallback,
        error: function(e) { // 失败后回调
            showToast("获取数据失败，请重试!");
        },
        complete: function(xhr, status) {
            document.getElementById('loadpagediv').style.display = "none";
        },
        beforeSend: function() {
            document.getElementById('loadpagediv').style.display = "block";
        }
    })
}

// 删除数据
var deleteData = function(url, data, returnJson, successCallback) {
    //如果是 json , server 必须返回内容
    var dataType = (returnJson == true) ? 'json' : 'text'
    $.ajax({
        async: true,
        cache: false,
        dataType: dataType,
        url: url,
        data: data,
        type: 'delete',
        success: successCallback,
        error: function(e) {
            showToast("更新数据失败，请重试!");
        },
        complete: function(xhr, status) {
            document.getElementById('loadpagediv').style.display = "none";
            $(".delete_btn").attr('disabled', false); //删除类 按钮允许点击
        },
        beforeSend: function() {
            document.getElementById('loadpagediv').style.display = "block";
            $(".delete_btn").attr('disabled', true); //删除类 按钮禁止点击
        }
    })
}

// 获取基础数据
function loadSysInfos() {
    var successCallback = function(data) {
        reflashWifiUI(data.wifi);
        crazyfmReflashUI(data.crazyfm);
        reflasheDesktopUI(data.desktop);
        reflashDeviceUI(data.device);
        reflashGroupAppUI(data.group)
        updateAssistantUI(data.assistant);
        reflashKeyboardUI(data.keyboard);
    }
    getData('/sys/infos', successCallback);
}

//------------------ Wifi ------------------

//保存 Wifi 信息

function saveWifiData() {
    var data = {
        ssid: $("#wifi-ssid").val(),
        password: $("#wifi-password").val()
    }
    $.post("/sys/wifi", data).always(checkUpdateResult);
}

function reflashWifiUI(data) {
    // document.getElementById("wifi-ssid").value = data.ssid;
    // document.getElementById("wifi-password").value = data.password;
    $('#wifi-ssid').val(data.ssid);
    $('#wifi-password').val(data.password);
}

$("#wifi-save-btn").click(function() {
    saveWifiData();
})

//------------------ desktop ------------------
function saveDesktopData() {
    var data = {
        desk_sign: $("#desk-sign").val(),
        desk_screensaver: $("desk-screensaver").val()
    }
    $.post("/app/desktop", data).always(checkUpdateResult);
}


function reflasheDesktopUI(data) {
    $('#desk-sign').val(data.desk_sign);
    $('#desk-screensaver').prop('checked', data.desk_screensaver);
}
//更新Desktop
$("#desk-save-btn").click(function() {
    saveDesktopData();
})

//------------------ CrazyFM ------------------

function saveCrazyfmData() {

    var data = {
        title_1: $("#crazyfm-1-title").val(),
        url_1: $("#crazyfm-1-url").val(),
        title_2: $("#crazyfm-2-title").val(),
        url_2: $("#crazyfm-2-url").val(),
        title_3: $("#crazyfm-3-title").val(),
        url_3: $("#crazyfm-3-url").val()
    }
    $.post("/app/crazyfm", data).always(checkUpdateResult);
}

function crazyfmReflashUI(data) {
    $('#crazyfm-1-title').val(data.title_1);
    $('#crazyfm-1-url').val(data.url_1);
    $('#crazyfm-2-title').val(data.title_2);
    $('#crazyfm-2-url').val(data.url_2);
    $('#crazyfm-3-title').val(data.title_3);
    $('#crazyfm-3-url').val(data.url_3);

}

$("#crazyfm-save-btn").click(function() {
    saveCrazyfmData();
})

//------------------ Device ------------------

function saveDeviceData() {
    color_r = Number($("#color-r").val());
    color_g = Number($("#color-g").val());
    color_b = Number($("#color-b").val());

    // reg = /[0-9]{1,2}/;
    // alert(reg.test(color_r));
    // alert(reg.test(color_g));
    // alert(reg.test(color_b));
    if (!(color_r >= 0 && color_r <= 255) ||
        !(color_g >= 0 && color_g <= 255) ||
        !(color_b >= 0 && color_b <= 255)) {
        alert("颜色RGB 必须是0～255数字");
        return;
    }

    var data = {
        // name: $("#device-name").val(),
        color_r: color_r,
        color_g: color_g,
        color_b: color_b,
        lock_gesutre: $("#lock-gesture").prop('checked'),
    }
    $.post("/sys/device", data).always(checkUpdateResult);
}

function reflashDeviceUI(data) {
    // $('#device-name').val(data.name);
    $('#color-r').val(data.color_r);
    $('#color-g').val(data.color_g);
    $('#color-b').val(data.color_b);
    $('#lock-gesture').prop('checked', data.lock_gesutre);
}

$("#device-save-btn").click(function() {
    saveDeviceData();
})



//------------------ Group APP ------------------

function saveGroupAppData() {
    var $li = $("#group_1_row").children("li")
    list = new Array();
    $li.each(function() {
        list.push($(this).attr("value"));
    });
    data = JSON.stringify({ 'g1': list })
    $.post("/sys/group", data).always(checkUpdateResult);
}


//刷新列表: data 是Json 数据, 具体格式请见 web_api.cpp
function reflashGroupAppUI(data) {
    var $g0 = $("#group_0_row");
    var $g1 = $("#group_1_row");
    $g0.children("li").remove();
    $g1.children("li").remove();

    for (let item of data.g0) {
        $g0.append("<li value=" + item.id + ">" + item.name + "</li>");
    }
    g1 = data.g1;
    for (let item of data.g1) {
        $g1.append("<li value=" + item.id + ">" + item.name + "</li>");
    }

}

$("#group-save-btn").click(function() {
    saveGroupAppData();
})

//------------------ Asst AI 助手 ------------------

function saveAssistantData() {
    asst_tts_voice = $("input:radio[name='tts-voice']:checked").val();
    if (asst_tts_voice == -1) //自定义
        asst_tts_voice = $("#tts-voice-custom").val();

    var data = {
        asst_id: $("#asst-id").val(),
        asst_secret: $("#asst-secret").val(),
        asst_tts_voice: asst_tts_voice,
        asst_nlp: $("input:radio[name='asst-nlp']:checked").val(),
        asst_openai_key: $('#asst-openai-key').val()
    }
    $.post("/sys/asst", data).always(checkUpdateResult);
}

//更新语音助手 UI
function updateAssistantUI(data) {
    $('#asst-id').val(data.asst_id);
    $('#asst-secret').val(data.asst_secret);
    //0　女生， 3 男生， 其他自定义
    if (data.asst_tts_voice == 0 || data.asst_tts_voice == 3) {
        $(":radio[name='tts-voice'][value='" + data.asst_tts_voice + "']").prop("checked", "checked");
    } else {
        $(":radio[name='tts-voice'][value='-1']").prop("checked", "checked");
        $("#tts-voice-custom").val(data.asst_tts_voice);
    }
    //nlp
    $(":radio[name='asst-nlp'][value='" + data.asst_nlp + "']").prop("checked", "checked");

    $('#asst-openai-key').val(data.asst_openai_key);
}

$("#asst-save-btn").click(function() {
    saveAssistantData();
})

//------------------ Keyboard ------------------
function initKeyboardOption() {

    KeyData = [{
        "name": "无",
        "value": "KEY_NONE"
    }, {
        "name": "CTRL",
        "value": "KEY_LEFT_CTRL"
    }, {
        "name": "ALT",
        "value": "KEY_LEFT_ALT"
    }, {
        "name": "SHIFT",
        "value": "KEY_LEFT_SHIFT"
    }, {
        "name": "win/cmd",
        "value": "KEY_LEFT_GUI"
    }, ];
    for (var key in KeyData) {
        document.getElementById("keyboard-select-up").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-down").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-left").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-right").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-clockwise").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-anticlockwise").options.add(new Option(KeyData[key].name, KeyData[key].value));
    }
    KeyData = [{
        "name": "无",
        "value": "KEY_NONE"
    }, {
        "name": "音量加+ : VOLUME_UP",
        "value": "KEY_MEDIA_VOLUME_UP"
    }, {
        "name": "音量减- : VOLUME_DOWN",
        "value": "KEY_MEDIA_VOLUME_DOWN"
    }, {
        "name": "静音 : MUTE",
        "value": "KEY_MEDIA_MUTE"
    }, {
        "name": "停止/播放 : PLAY_PAUSE",
        "value": "KEY_MEDIA_PLAY_PAUSE"
    }, {
        "name": "下一首 : NEXT_TRACK",
        "value": "KEY_MEDIA_NEXT_TRACK"
    }, {
        "name": "上一首 : PREVIOUS_TRACK",
        "value": "KEY_MEDIA_PREVIOUS_TRACK"
    }, {
        "name": "上 : UP",
        "value": "KEY_UP_ARROW"
    }, {
        "name": "下 : DOWN",
        "value": "KEY_DOWN_ARROW"
    }, {
        "name": "左 : LEFT",
        "value": "KEY_LEFT_ARROW"
    }, {
        "name": "右 : RIGHT",
        "value": "KEY_RIGHT_ARROW"
    }, {
        "name": "上一页 : PAGE_UP",
        "value": "KEY_PAGE_UP"
    }, {
        "name": "下一页 : PAGE_DOWN",
        "value": "KEY_PAGE_DOWN"
    }, {
        "name": "首页 : HOME",
        "value": "KEY_HOME"
    }, {
        "name": "回车 : RETURN",
        "value": "KEY_RETURN"
    }, {
        "name": "取消 : ESC",
        "value": "KEY_ESC"
    }, {
        "name": "空格",
        "value": "KEY_SPACE"
    }, {
        "name": "F1",
        "value": "KEY_F1"
    }, {
        "name": "F2",
        "value": "KEY_F2"
    }, {
        "name": "F3",
        "value": "KEY_F3"
    }, {
        "name": "F4",
        "value": "KEY_F4"
    }, {
        "name": "F5",
        "value": "KEY_F5"
    }, {
        "name": "F6",
        "value": "KEY_F6"
    }, {
        "name": "F7",
        "value": "KEY_F7"
    }, {
        "name": "F8",
        "value": "KEY_F8"
    }, {
        "name": "F9",
        "value": "KEY_F9"
    }, {
        "name": "F10",
        "value": "KEY_F10"
    }, {
        "name": "F11",
        "value": "KEY_F11"
    }, {
        "name": "F12",
        "value": "KEY_F12"
    }];

    for (var key in KeyData) {
        document.getElementById("keyboard-select-up-2").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-down-2").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-left-2").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-right-2").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-clockwise-2").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-anticlockwise-2").options.add(new Option(KeyData[key].name, KeyData[key].value));
    }
    KeyData = [{
        "name": "无",
        "value": "KEY_NONE"
    }, {
        "name": "0",
        "value": "0"
    }, {
        "name": "1",
        "value": "1"
    }, {
        "name": "2",
        "value": "2"
    }, {
        "name": "3",
        "value": "3"
    }, {
        "name": "4",
        "value": "4"
    }, {
        "name": "5",
        "value": "5"
    }, {
        "name": "6",
        "value": "6"
    }, {
        "name": "7",
        "value": "7"
    }, {
        "name": "8",
        "value": "8"
    }, {
        "name": "9",
        "value": "9"
    }, {
        "name": "A",
        "value": "A"
    }, {
        "name": "B",
        "value": "B"
    }, {
        "name": "C",
        "value": "C"
    }, {
        "name": "D",
        "value": "D"
    }, {
        "name": "E",
        "value": "E"
    }, {
        "name": "F",
        "value": "F"
    }, {
        "name": "G",
        "value": "G"
    }, {
        "name": "H",
        "value": "H"
    }, {
        "name": "I",
        "value": "I"
    }, {
        "name": "J",
        "value": "J"
    }, {
        "name": "K",
        "value": "K"
    }, {
        "name": "L",
        "value": "L"
    }, {
        "name": "M",
        "value": "M"
    }, {
        "name": "N",
        "value": "N"
    }, {
        "name": "O",
        "value": "O"
    }, {
        "name": "P",
        "value": "P"
    }, {
        "name": "Q",
        "value": "Q"
    }, {
        "name": "R",
        "value": "R"
    }, {
        "name": "S",
        "value": "S"
    }, {
        "name": "T",
        "value": "T"
    }, {
        "name": "U",
        "value": "U"
    }, {
        "name": "V",
        "value": "V"
    }, {
        "name": "W",
        "value": "W"
    }, {
        "name": "X",
        "value": "X"
    }, {
        "name": "Y",
        "value": "Y"
    }, {
        "name": "Z",
        "value": "Z"
    }, ];
    for (var key in KeyData) {
        document.getElementById("keyboard-select-up-3").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-down-3").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-left-3").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-right-3").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-clockwise-3").options.add(new Option(KeyData[key].name, KeyData[key].value));
        document.getElementById("keyboard-select-anticlockwise-3").options.add(new Option(KeyData[key].name, KeyData[key].value));
    }
}

function reflashKeyboardUI(data) {
    $("#keyboard-name").val(data.kb_name);
    var cmd = data.kb_up.split("#_#");
    $("#keyboard-select-up").val(cmd[0]);
    $("#keyboard-select-up-2").val(cmd[1]);
    $("#keyboard-select-up-3").val(cmd[2]);
    cmd = data.kb_down.split("#_#");
    $("#keyboard-select-down").val(cmd[0]);
    $("#keyboard-select-down-2").val(cmd[1]);
    $("keyboard-select-down-3").val(cmd[2]);
    cmd = data.kb_left.split("#_#");
    $("#keyboard-select-left").val(cmd[0]);
    $("#keyboard-select-left-2").val(cmd[1]);
    $("#keyboard-select-left-3").val(cmd[2]);
    cmd = data.kb_right.split("#_#");
    $("#keyboard-select-right").val(cmd[0]);
    $("#keyboard-select-right-2").val(cmd[1]);
    $("#keyboard-select-right-3").val(cmd[2]);
    cmd = data.kb_cw.split("#_#");
    $("#keyboard-select-clockwise").val(cmd[0]);
    $("#keyboard-select-clockwise-2").val(cmd[1]);
    $("#keyboard-select-clockwise-3").val(cmd[2]);
    cmd = data.kb_anticw.split("#_#");
    $("#keyboard-select-anticlockwise").val(cmd[0]);
    $("#keyboard-select-anticlockwise-2").val(cmd[1]);
    $("#keyboard-select-anticlockwise-3").val(cmd[2]);
}

function saveKeyboardData() {
    var kb_name = $("#keyboard-name").val();
    var kb_up = $("#keyboard-select-up").val() + "#_#" + $("#keyboard-select-up-2").val() + "#_#" + $("#keyboard-select-up-3").val();
    var kb_down = $("#keyboard-select-down").val() + "#_#" + $("#keyboard-select-down-2").val() + "#_#" + $("#keyboard-select-down-3").val();
    var kb_left = $("#keyboard-select-left").val() + "#_#" + $("#keyboard-select-left-2").val() + "#_#" + $("#keyboard-select-left-3").val();
    var kb_right = $("#keyboard-select-right").val() + "#_#" + $("#keyboard-select-right-2").val() + "#_#" + $("#keyboard-select-right-3").val();
    var kb_cw = $("#keyboard-select-clockwise").val() + "#_#" + $("#keyboard-select-clockwise-2").val() + "#_#" + $("#keyboard-select-clockwise-3").val();
    var kb_anticw = $("#keyboard-select-anticlockwise").val() + "#_#" + $("#keyboard-select-anticlockwise-2").val() + "#_#" + $("#keyboard-select-anticlockwise-3").val();

    var data = {
        kb_name: kb_name,
        kb_up: kb_up,
        kb_down: kb_down,
        kb_left: kb_left,
        kb_right: kb_right,
        kb_cw: kb_cw,
        kb_anticw: kb_anticw
    }
    $.post("/sys/keyboard", data).always(checkUpdateResult);
}

$("#keyboard-save-btn").click(function() {
    saveKeyboardData();
})

//------------------Photo 游戏机------------------
//得到行对象
function getRowObj(obj) {
    var i = 0;
    while (obj.tagName.toLowerCase() != "tr") {
        obj = obj.parentNode;
        if (obj.tagName.toLowerCase() == "table") return null;
    }
    return obj;
}

//根据得到的行对象得到所在的行数
function getRowNo(obj) {
    var trObj = getRowObj(obj);
    var trArr = trObj.parentNode.children;
    for (var trNo = 0; trNo < trArr.length; trNo++) {
        if (trObj == trObj.parentNode.children[trNo]) {
            alert(trNo + 1);
        }
    }
}

//删除行
function delRow(obj) {
    var tr = this.getRowObj(obj);
    if (tr != null) {
        tr.parentNode.removeChild(tr);
    } else {
        throw new Error("the given object is not contained by the table");
    }
}

function buttonClick_DeletePhoto(obj) {
    var tr = this.getRowObj(obj);
    var res = confirm(`确定要删除此文件吗？ ${tr.id} `);
    var data = {
        reboot: 1
    }
    if (res) {
        var data = {
            file_name: tr.id
        }
        var successCallback = function(data) {
            delRow(obj);
            reflashPhotoSizeUI(data.meta);
        }
        deleteData("/app/photo", data, true, successCallback);
    }
}

function reflashPhotoSizeUI(data) {
    // document.getElementById('gif-file-total').innerHTML = data.file_total;
    $("#photo-file-total").html(data.file_total);
    $("label.file-remain").html(data.file_remain);
}

function reflashPhotoFileUI(data) {

    $("#table-photo  tr:not(:first)").html(""); //第一行 标题不删

    for (let file of data) {
        var tr = document.createElement("tr");
        tr.id = file.name; //后续删除 内容按此ID 为准

        var td_name = document.createElement("td");
        td_name.innerHTML = file.name;

        var td_size = document.createElement("td");
        td_size.innerHTML = file.size_rd;

        var td_btn_del = document.createElement("td");
        td_btn_del.innerHTML = '<button  class ="delete_btn" onclick="buttonClick_DeletePhoto(this)">删除</button>'

        tr.appendChild(td_name);
        tr.appendChild(td_size);
        tr.appendChild(td_btn_del);
        document.getElementById('table-photo').appendChild(tr);
    }
}
var photo_has_inited = false;

function loadPhotoInfo() {
    var successCallback = function(data) {
        reflashPhotoFileUI(data.files);
        reflashPhotoSizeUI(data.meta);
        photo_has_inited = true;
    }
    getData('/app/photo', successCallback);

}
// Gif 文件上传
$(document).ready(function() {
    $('#photo_upload_input').change(function() {
        $(this).simpleUpload("/app/photo/upload", {
            start: function(file) {
                var filename = file.name;
                var filename_lowercase = filename.toLowerCase();
                if (!filename_lowercase.endsWith(".jpeg") && !filename_lowercase.endsWith(".jpg") &&
                    !filename_lowercase.endsWith(".png")) {
                    alert("请选择 照片");
                    that.upload.cancel();
                    return;
                }
                //正则判断： 只允许 字母，数字 下划线 . 组成。 
                // \w 表示[0－9a-zA-Z_] ; + 表示匹配一个或一个以上;
                var reqex = /^\w.+$/
                if (!reqex.test(filename)) {
                    alert("文件名格式只允许字母和数字, 请重新选择");
                    that.upload.cancel();
                    return;
                }
                //upload started
                $(".upload_btn").attr('disabled', true); //上传类 按钮禁止点击
                document.getElementById('loadpagediv').style.display = "block";
                $('#photo_upload_filename').html(`文件：${filename}  `);
                $('#photo_upload_state').html("");

            },

            progress: function(progress) {
                $('#photo_upload_state').html("上传中: " + Math.round(progress) + "%");
            },

            success: function(data) {
                //upload successful
                document.getElementById('loadpagediv').style.display = "none";
                $(".upload_btn").attr('disabled', false); //上传类 按钮允许点击
                $('#photo_upload_state').html("上传成功");
                console.log("上传成功: " + JSON.stringify(data));

                loadPhotoInfo(); //上传成功后刷新列表   
            },
            error: function(error) {
                //upload failed
                document.getElementById('loadpagediv').style.display = "none";
                $(".upload_btn").attr('disabled', false); //上传类 按钮允许点击
                $('#photo_upload_state').html("上传失败");
                console.log("上传失败: " + error.name + ": " + error.message);

            }
        });
    });
});


//------------------菜单------------------
//重启按钮
function rebootSys() {
    var res = confirm("要重新启动立方豆吗？");
    var data = {
        reboot: 1
    }
    if (res) {
        $.post("/sys/reboot", data).always(checkUpdateResult);
        alert("重启了～");
    }
}

$("#reboot-btn").click(function() {
    rebootSys();
})


//tag 切换
function tabSelected(tab) {
    //切换到 tab更新数据，如果没有初始化则获取列表并更新 UI
    if (tab == '#c_photo' && !photo_has_inited)
        loadPhotoInfo();
}