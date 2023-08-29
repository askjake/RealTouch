import commands from './commands.json' assert {type: "json"};
console.log(commands);

const ipButton = document.querySelector("#ipAddress");
const ipLabel = document.querySelector("#ipLabel");

ipButton.onclick = () => {
    let ip = prompt("What is the IP Address of the remote?");
    alert(ip + " was set as ip.");
    console.log(`remote ip address set to ${ip}`);
    ipLabel.textContent = ip;
    return ip;
}

window.onload = function() {
    let ip = prompt("What is the IP Address of the remote? \nExample: 10.74.111.58");
    alert(ip + " was set as ip.");
    console.log(`remote ip address set to ${ip}`);
    ipLabel.textContent = ip;
    let txt = "";
    txt = ""
    for (let x in commands.commands) {
        txt += console.log(commands.commands[x])
        document.getElementById(commands.commands[x]).action = `http://${ip}/54/${commands.commands[x]}`;
        document.getElementById(commands.commands[x]).submit();
    }
    for (let y in commands.unusedCommands) {
        txt += console.log(commands.unusedCommands[y])
        document.getElementById(commands.unusedCommands[y]).action = `http://${ip}/54/${commands.unusedCommands[y]}`;
        document.getElementById(commands.unusedCommands[y]).submit();
    }
    setTimeout(function(){
        console.log("waited 1 second");
    }, 1000)
    fetch(`http://${ip}/54/${commands.commands['Reset Remote']}`)

    return ip
}