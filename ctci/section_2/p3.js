
var LinkedList = require('./linked_list').LinkedList;

var link = new LinkedList();
link.push(7);
link.push(2);
link.push(1);
link.push(4);
link.push(5);

function delete_node(node) {
	node.value = node.next.value;
	node.next = node.next.next;
}

link.print();
delete_node(link.head.next.next);
link.print()