// implementation of a linked list in JS
// taken from https://www.thatjsdude.com/interview/linkedList.html

function LinkedList(){  
  this.head = null;
}

LinkedList.prototype.push = function(val) {
	var node = {
		value: val,
		next: null
	}
	if (!this.head) {
		this.head = node;
	} else {
		current = this.head;
		while (current.next) {
			current = current.next;
		}
		current.next = node;
	}
}

LinkedList.prototype.print = function() {
	var temp = this.head;
	while (temp.next != null) {
		console.log(temp.value);
		temp = temp.next;
	}
	console.log(temp.value);
}

module.exports = { LinkedList: LinkedList };