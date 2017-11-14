// Remove Dups

var LinkedList = require('./linked_list').LinkedList;

// console.log(LinkedList);
var link = new LinkedList();
link.push(5);
link.push(5);
link.push(4);
link.push(7);
link.push(6);
link.push(4);

console.log("before", link.head);

function remove_dup(linked_list) {
	var temp = linked_list.head;
	var buffer = {};
	prev = {next: linked_list.head};
	while (temp.next !== null) {
		if (buffer.hasOwnProperty(temp.value)) {
			prev.next = temp.next;
		} else {
			buffer[temp.value] = true;
			prev = prev.next;
		}
		temp = temp.next;
	}
	linked_list.print();
}

remove_dup(link);