const endPoint = window.location.hostname === "localhost" ? `http://demo1.local` : "";
let currentFile = null;

async function refreshFiles() {
    try {
        const response = await fetch(`${endPoint}/files`);
        const data = await response.json();

        if (data.status !== "success") {
            console.error("Error fetching files:", data.message);
            return;
        }

        const fileList = document.getElementById('fileList');
        fileList.innerHTML = '';

        data.data.files.forEach(file => {
            const li = document.createElement('li');
            li.textContent = file;
            li.onclick = () => openFile(file);
            fileList.appendChild(li);
        });
    } catch (err) {
        console.error('Error fetching file list:', err);
    }
}

async function openFile(file) {
    try {
        const response = await fetch(`${endPoint}/file?filename=${encodeURIComponent(file)}`);
        const content = await response.text();

        document.getElementById('editor').value = content;
        currentFile = file;
    } catch (err) {
        console.error('Error opening file:', err);
    }
}

async function saveFile() {
    if (!currentFile) {
        alert('No file selected.');
        return;
    }

    const content = document.getElementById('editor').value;
    try {
        const response = await fetch(`${endPoint}/file?filename=${encodeURIComponent(currentFile)}`, {
            method: 'POST',
            headers: { 'Content-Type': 'text/plain' },
            body: content
        });

        const data = await response.json();
        if (data.status !== 'success') {
            alert('Failed to save file.');
        }
    } catch (err) {
        console.error('Error saving file:', err);
    }
}

async function newFile() {
    const fileName = prompt('Enter new file name:');
    if (!fileName) return;

    try {
        const response = await fetch(`${endPoint}/file?filename=${encodeURIComponent(fileName)}`, {
            method: 'POST',
            headers: { 'Content-Type': 'text/plain' },
            body: ''
        });
        const data = await response.json();
        if (data.status === 'success') {
            refreshFiles();
        } else {
            alert('Failed to create file.');
        }
    } catch (err) {
        console.error('Error creating file:', err);
    }
}

async function deleteFile() {
    if (!currentFile) {
        alert('No file selected.');
        return;
    }

    if (!confirm(`Are you sure you want to delete ${currentFile}?`)) return;

    try {
        const response = await fetch(`${endPoint}/file?filename=${encodeURIComponent(currentFile)}`, {
            method: 'DELETE'
        });

        const data = await response.json();
        if (data.status === 'success') {
            currentFile = null;
            document.getElementById('editor').value = '';
            refreshFiles();
        } else {
            alert('Failed to delete file.');
        }
    } catch (err) {
        console.error('Error deleting file:', err);
    }
}

async function renameFile() {
    if (!currentFile) {
        alert('No file selected.');
        return;
    }

    const newName = prompt('Enter new name for the file:', currentFile);
    if (!newName) return;

    try {
        const response = await fetch(`${endPoint}/rename`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ oldname: currentFile, newname: newName })
        });

        const data = await response.json();
        if (data.status === 'success') {
            currentFile = newName;
            refreshFiles();
        } else {
            alert('Failed to rename file.');
        }
    } catch (err) {
        console.error('Error renaming file:', err);
    }
}

refreshFiles();