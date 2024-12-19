function bubble(array: number[]) {
    for (let i = 0; i < array.length; i++) {
        for (let y = array.length - 2; y >= i; y--) {
//            console.log(`array[${i}] = ${array[i]}, array[${y}] = ${array[y]}`);
        
            if (array[y] > array[y + 1]) {
                let temp = array[y];
                array[y] = array[y + 1];
                array[y + 1] = temp;
            }
        }
    }

    return array;
}

let array: number[] = [23, 1, 32, 54, 12, 99, 15, 66];
console.log(...array);

array = bubble(array);

console.log(...array);
