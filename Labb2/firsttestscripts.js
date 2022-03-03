
console.log("Hello World");

class Iterator {
    constructor(arr, pos) {
        this.inputArray = arr;
        this.lhs = pos;
        this.rhs = this.inputArray.length;
    }

    hasNext () {
        console.log('Running hasNext Function');
        if(this.lhs+1 < this.rhs){
            return true;
        }
        else{
            return false;
        }
    }

    next () {
        console.log('Running next Function');
        let it = new Iterator(this.inputArray, this.lhs+1);
        return it;
    }
    print () {
        console.log(this.lhs);
    }
}

//Declare array
const arr = [1, 5, 2, 5, 0];

// create object
let it = new Iterator(arr, 0);
console.log(it.inputArray);
console.log("Iterator Position: " + it.lhs);
console.log("Array Size: " + it.rhs);

while(it.hasNext()){
    it.print();
    it = it.next();
}
it.print();

console.log("End of Program");