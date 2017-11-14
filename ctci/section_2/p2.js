
var LinkedList = require('./linked_list').LinkedList;

var link = new LinkedList();
link.push(7);
link.push(2);
link.push(1);
link.push(4);
link.push(5);

function kth_to_last(linked_list, k) {
	var a = linked_list.head;
	for (var i = 0; i < k - 1; i++) {
		a = a.next;
	}
	var b = linked_list.head;
	while (a.next !== null) {
		// console.log(a.value, b.value);
		a = a.next;
		b = b.next;
	}
	console.log(b.value);
}

// link.print();
kth_to_last(link, 3);