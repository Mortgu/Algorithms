function bubble(array) {
    for (var i = 0; i < array.length; i++) {
        for (var y = array.length - 2; y >= i; y--) {
            //            console.log(`array[${i}] = ${array[i]}, array[${y}] = ${array[y]}`);
            if (array[y] > array[y + 1]) {
                var temp = array[y];
                array[y] = array[y + 1];
                array[y + 1] = temp;
            }
        }
    }
    return array;
}
var array = [23, 1, 32, 54, 12, 99, 15, 66];
console.log.apply(console, array);
array = bubble(array);
console.log.apply(console, array);
