(() => {
    // Currency
    const curreny = data.currency;
    let currencyEle = document.getElementsByClassName('currency');
    for (let i = 0; i < currencyEle.length; i++) {
        currencyEle[i].innerHTML = curreny;
    }
    // All trades
    const allTrades = data.all_trades;
    for (const key in allTrades) {
        if (allTrades.hasOwnProperty(key)) {
            const id = allTrades[key].id;
            const type = allTrades[key].type;
            let help = allTrades[key].help;
            let value = allTrades[key].value;

            if (id === 1020) {
                let val1 = parseInt(value);
                let val2 = String(value - val1).slice(2, 4);

                if (document.getElementById('1020_A_1') && document.getElementById('1020_A_2')) {
                    document.getElementById('1020_A_1').innerText = val1;
                    document.getElementById('1020_A_2').innerText = val2;
                }
                continue;
            }

            if (type !== "string") {
                value = parseFloat(parseFloat(allTrades[key].value).toFixed(2).toString()).toLocaleString('en-CA')
            }

            if (document.getElementById(`${id}_A`)) {
                document.getElementById(`${id}_A`).innerText = value;


                const helpEle = document.getElementById(`help_${id}_A`)
                if (helpEle) {
                    help = help ? help : 'not found';
                    helpEle.setAttribute('title', help);
                }
            }
        }
    }

    //Long trades
    const longTrades = data.long_only;
    for (const key in longTrades) {
        if (longTrades.hasOwnProperty(key)) {
            const id = longTrades[key].id;
            const type = allTrades[key].type;
            let value = allTrades[key].value;
            if (type !== "string") {
                value = parseFloat(parseFloat(allTrades[key].value).toFixed(2).toString()).toLocaleString('en-CA')
            }

            if (document.getElementById(`${id}_L`)) {
                document.getElementById(`${id}_L`).innerText = value;
            }
        }
    }

    //Short trades
    const shortTrades = data.short_only;
    for (const key in shortTrades) {
        if (shortTrades.hasOwnProperty(key)) {
            const id = shortTrades[key].id;
            const type = allTrades[key].type;
            let value = allTrades[key].value;
            if (type !== "string") {
                value = parseFloat(parseFloat(allTrades[key].value).toFixed(2).toString()).toLocaleString('en-CA')
            }

            if (document.getElementById(`${id}_S`)) {
                document.getElementById(`${id}_S`).innerText = value;
            }
        }
    }

    // Event listeners
    let togglers = document.getElementsByClassName('toggle-img');
    var toggle = function () {
        const style = getComputedStyle(this);
        const backgroundImage = style.backgroundImage;
        if (backgroundImage.indexOf('toggle1') > 0) {
            this.style.backgroundImage = backgroundImage.replace('toggle1', 'toggle2');
        } else {
            this.style.backgroundImage = backgroundImage.replace('toggle2', 'toggle1');
        }

        const _target = this.getAttribute('data-target');
        const target = document.getElementsByClassName(_target)[0];
        target.classList.toggle("hide");
    };

    for (var i = 0; i < togglers.length; i++) {
        togglers[i].addEventListener('click', toggle, false);
    }
})();