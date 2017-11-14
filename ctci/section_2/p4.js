
var LinkedList = require('./linked_list').LinkedList;

var link = new LinkedList();
link.push(7);
link.push(2);
link.push(1);
link.push(4);
link.push(5);

function partition(linked_list, x) {
	var arr = [];
	var runner = linked_list.head;
	while (runner !== null) {
		if (runner.value < x) {
			arr.push(runner.value);
			if (runner.next === null) {
				runner.value = null;
			} else {
				runner.value = runner.next.value;
				runner.next = runner.next.next;
			}
		} else {
			runner = runner.next;
		}
	}

	for (var i = 0; i < arr.length; i++) {
		var val = arr[i];
		var new_node = {
			value: val,
			next: linked_list.head
		};
		linked_list.head = new_node;
	}
	return linked_list
}

link.print();
partition(link, 4);
link.print();