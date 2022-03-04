function Iterator(arr){
    this.index = 0;
    this.length = arr.length;
    this.hasNext = function(){
        if(this.index < this.length){
            return true;
        }
        else{
            return false;
        }
    }
    this.next = function(){
        return arr[this.index++];
    }
}

Array.prototype.iterator = function(){
    return new Iterator(this);
}

arr = [11, 22, 33, 44, 55];
f = arr.iterator();

while(f.hasNext()){
    console.log(f.next());
}