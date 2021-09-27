
function dataProcess(input) {
    let file = input.files[0];
    let reader = new FileReader();
    reader.readAsText(file,'windows-1251'); // чтение из файла
    reader.onload = () => { // после прочтения выполнить функцию
        let data = reader.result.split('\n'); // записать результат в массив data построчно
        let processedData ={
            name: [],
            reqInHour: [],
            hours: [],
            reqOverall: [],
            addInfo: []
        };
        data.forEach(line => {
            let strData = line.split(' '); // разделяем текущую запись на составные элементы
            let pos = [];
            if (processedData.name.length === 0) { // если еще нет никаких записей
                processedData.name[0] = strData[0]; // то добавь первую запись
                processedData.reqInHour[0] = parseInt(strData[1]);
                processedData.hours[0] = parseInt(strData[2]);
                processedData.reqOverall[0] = processedData.reqInHour[0] * processedData.hours[0];
                processedData.addInfo[0] = strData[3];
            } else {
                pos = processedData.name.findIndex(item => item === strData[0]) // поиск позиции с именем в обрабатываемой строке
                if (pos >= 0) {   // позиция с таким именем найдена
                    processedData.name[pos] = strData[0];
                    processedData.reqInHour[pos] = processedData.reqInHour[pos] + parseInt(strData[1]);
                    processedData.hours[pos] = processedData.hours[pos] + parseInt(strData[2]);
                    processedData.reqOverall[pos] = processedData.reqOverall[pos] + parseInt(strData[1])*parseInt(strData[2]);
                    processedData.addInfo[pos] = strData[3];
                } else { // иначе если такого имени в списках еще нет
                    processedData.name.push(strData[0]); // добавить имя и все данные
                    processedData.reqInHour.push(parseInt(strData[1])); // добавить имя и все данные
                    processedData.hours.push(parseInt(strData[2])); // добавить имя и все данные
                    processedData.reqOverall.push(parseInt(strData[1])*parseInt(strData[2])); // добавить имя и все данные
                    processedData.addInfo.push(strData[3]); // добавить имя и все данные

                }
            }

        })
        let buf = processedData.name.map(function(item, i) { // массив со свойствами: индексы и соответсвующие первые буквы имени
            return { index: i, value: item[0]};
        });
        buf.sort((a, b) => { // сортировка массива по первым буквам имени
            if (a.value > b.value) {
                return 1; }
            if (a.value < b.value) {
                return -1; }
            return 0;
        });
        let sortedData ={
            name: [],
            reqInHour: [],
            hours: [],
            reqOverall: [],
            addInfo: []
        };
        // сортировка всех данных по имени
        sortedData.name = buf.map(elem => {
            return processedData.name[elem.index];
        })
        sortedData.reqInHour = buf.map(elem => {
            return processedData.reqInHour[elem.index];
        })
        sortedData.hours = buf.map(elem => {
            return processedData.hours[elem.index];
        })
        sortedData.reqOverall = buf.map(elem => {
            return processedData.reqOverall[elem.index];
        })
        sortedData.addInfo = buf.map(elem => {
            return processedData.addInfo[elem.index];
        })

        // запись в отсортированных данных в 1 массив
        let outData = [];
        for (let i = 0; i < sortedData.name.length; i++) {
            outData[i] = `${sortedData.name[i]} ${sortedData.reqInHour[i]} ${sortedData.hours[i]} ${sortedData.reqOverall[i]} ${sortedData.addInfo[i]}\r`;
        }

        // вывод в файл
        let save = document.getElementById('aref');
        let blob = new Blob([outData.join('\n')],{type: "text/plain"})
        save.setAttribute("href",URL.createObjectURL(blob))
        save.click()
    };
}
