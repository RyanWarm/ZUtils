public class LinkedlistSort {
	class Node {
		public int value;
		public Node next;
		public Node(int v) {
			value = v;
			next = null;
		}
	}

	public void swapNode( Node l, Node r ) {
		Node tmp = new Node(l.value);
		tmp.next = l.next;
		l.value = r.value;
		l.next = r.next;
		r.value = tmp.value;
		r.next = tmp.next;
	}

	public Node performSort( Node head, Node tail ) {
		Node l = head;
		while( l.next != null && l.next.value <= head.value ) l = l.next;
		Node r = l.next;
		while( r != null && r.value > head.value) r = r.next;
		while( head != tail && tail != null ) {
			l = l.next;
			swapNode(l,r);
			while( r != null && r.value > head.value) r = r.next;
		}
		swapNode(head,l);
		return head;
	}

	public Node sort( Node head ) {
		Node tail = head;
		while( tail.next != null ) {
			tail = tail.next;
		}
		return performSort(head, tail);
	}

	public static void main( String[] args ) {

	}
}
