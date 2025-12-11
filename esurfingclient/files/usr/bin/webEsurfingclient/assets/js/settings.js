// 静态内容
const showPwdBtn = document.getElementById('show-pwd');
const staticPwdInput = document.getElementById('static-pwd');
const staticUsrInput = document.getElementById('static-usr');
const staticChnPC = document.getElementById('static-chn-pc');
const staticChnPhone = document.getElementById('static-chn-phone');
const staticDebugOn = document.getElementById('static-debug-on');
const staticDebugOff = document.getElementById('static-debug-off');
const staticSmallOn = document.getElementById('static-small-on');
const staticSmallOff = document.getElementById('static-small-off');

showPwdBtn.addEventListener('click', () => {
    if (staticPwdInput.type === 'password') {
        staticPwdInput.type = 'text';
        showPwdBtn.textContent = '隐藏密码';
    } else {
        staticPwdInput.type = 'password';
        showPwdBtn.textContent = '显示密码';
    }
})
// 模态框
const settingsModalBtn = document.getElementById('settings-change-btn');
const settingsModal = document.getElementById('settings-modal');
const modalContainer = document.getElementById('settings-modal-container');
const cancelBtn = document.getElementById('settings-cancel');

settingsModalBtn.addEventListener('click', () => {
    if (!settingsModal.classList.contains('modalact')) settingsModal.classList.add('modalact');
});

document.addEventListener('click', e => {
    if ((!modalContainer.contains(e.target) && !settingsModalBtn.contains(e.target) && settingsModal.classList.contains('modalact')) || cancelBtn.contains(e.target)) {
        settingsModal.classList.remove('modalact');
    }
});

// 远程
async function getSettings() {
    await fetch('/api/getSettings')
        .then(res => res.json())
        .then(data => {
            staticUsrInput.value = data.username;
            staticPwdInput.value = data.password;

            if (data.channel === 'pc') {
                staticChnPhone.classList.remove('btnon');
                staticChnPC.classList.add('btnon');
            } else {
                staticChnPC.classList.remove('btnon');
                staticChnPhone.classList.add('btnon');
            }

            if (data.debug) {
                staticDebugOff.classList.remove('btnon');
                staticDebugOn.classList.add('btnon');
            } else {
                staticDebugOn.classList.remove('btnon');
                staticDebugOff.classList.add('btnon');
            }

            if (data.smallDevice) {
                staticSmallOff.classList.remove('btnon');
                staticSmallOn.classList.add('btnon');
            } else {
                staticSmallOn.classList.remove('btnon');
                staticSmallOff.classList.add('btnon');
            }
        })
        .catch(err => console.log(err));
}