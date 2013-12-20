function Node(data){
    this.data = data;
    this.index = NaN;
    this.next = null, this.prev = null;
}

function ListIter(list){
    this.list = list;
    this.node = list.head;

    this.next = function(){
        return this.node.next;
    }

    this.prev = function(){
        return this.node.prev;
    }

    this.remove = function(){
        this.node.prev.next = this.node.next;
        this.node.next.prev = this.node.prev;
    }
}

function List(){
    this.head = null;
    this.tail = null;

    this.length = 0;

    // insert at (index)
    // get at (index)
    // remove at (index)

    this.push = function(data){
        if(this.head == null){
            this.head = new Node(data);
            this.tail = this.head;
            this.tail.length = this.length;
        }
        else{
            this.tail.next = new Node(data);
            this.tail.next.prev = this.tail;
            this.tail = this.tail.next;
            this.tail.index = this.length;
        }

        this.length += 1;
        return true;
    }

    this.pop = function(data){
        if(this.head == null)
            return null;

        if(this.tail == null)
            return null;

        var n = this.tail;
        this.tail = this.tail.prev;
        this.tail.next = null;

        return n.data;
    }

    // removes all nodes where data == node.data
    this.remove = function(data){
        if(this.head == null)
            return false;

        if(this.tail == null)
            return false;

        var self = this;
        this.each(function(el){
            if(el.data == data){
                if(el == self.head){
                    // head
                    self.head = self.head.next;
                    self.head.prev = null;
                }
                else if(el == self.tail){
                    // tail
                    self.tail = self.tail.prev;
                    self.tail.next = null;
                }
                else{
                    var n = el.next;
                    var p = el.prev;
                    n.prev = p;
                    p.next = n;
                }

                el.prev = null;
                el.next = null;
            }
        });

        return false;
    }

    this.each = function(fn){
        var n = this.head;
        while(n != null){
            fn(n);

            n = n.next;
        }
    }

}