
public class RoutingMapTree
{
	Exchange node;
	//Constructor
	RoutingMapTree(){
		node = new Exchange(0);
	}
	//switchOn(MobilePhone a, Exchange b) : 
	public void switchOn(MobilePhone a, Exchange b){
		try{
		if(a.status()){ throw new MyException();}
		else{
			a.switchOn();
			b.residentSet().add(a);
		}
		}
		catch(MyException ex){System.out.println("Error : Already switchOn");}
	}
	
	//switchOff(MobilePhone a) : 
	public void switchOff(MobilePhone a){
		if(a.status()){ 
			Exchange loc = a.location();
			a.switchOff();
			loc.residentSet().delete(a);
		}
	}
	//search(int id) :
	public Exchange searchNode(int id){
		Exchange fina;
		
		if(this.node.data == id){return this.node;}
		else{ 
			RoutingMapTree var6;
			for(int i=0;i<this.node.numChildren();i++)
			{
				var6=(this.node).subtree(i);
				fina=var6.searchNode(id);
				if(fina!=null)
				{
					return fina;
				}
			}
			return null;
		}
			
	}
		

	//getNextNode(int id) :
	public Exchange getNextNode(int id){
		for(int i=0;i<this.node.residentSet().size();i++){
			if(this.node.residentSet().getIdAt(i) == id){ 
				return this.node.residentSet().getAt(i).location();
			}
		}
		/*try{
			throw new MyException();
		}
		catch(MyException ex){System.out.println("Error : MobilePhone does not exist in Tree.");}*/
		Exchange a = new Exchange(0);
		return a;
	}
				
	//performAction(String actionMessage) : Perform action given in message.
	public String performAction(String actionMessage){
		String job,a="",b="",output = "";
		char letter;
		int i=0,val_a,val_b;
		while(actionMessage.charAt(i) != ' '){i++;}
		switch(i){
			case 11 :
				i = 12;
				while(actionMessage.charAt(i) != ' '){ a = a + actionMessage.charAt(i);i++;}
				b = actionMessage.substring(i+1,actionMessage.length());
				val_a = Integer.parseInt(a);
				val_b = Integer.parseInt(b);
				//Main Work
				
					Exchange bth = new Exchange(val_b);
					this.searchNode(val_a).setChild(bth);
				
		
				break;
			case 14 :
				i = 15;
				while(actionMessage.charAt(i) != ' '){ a = a + actionMessage.charAt(i);i++;}
				b = actionMessage.substring(i+1,actionMessage.length());
				val_a = Integer.parseInt(a);
				val_b = Integer.parseInt(b);
				//Main Work
				
					Exchange var1 = this.searchNode(val_b);
					int flag = 0;
					
					for(int k = 0; k<var1.residentSet().size();k++){
						if(var1.residentSet().getIdAt(k) == val_b){flag =1;break;}
					}
					if(flag == 0){
					
						MobilePhone var2 = new MobilePhone(val_a);
						var2.switchOn();
						//var2.location() = var1;
						var1.residentSet().add(var2);
					
					}
					
				
				break;
			case 13 :
				i = 14;
				while(actionMessage.charAt(i) != ' '){ a = a + actionMessage.charAt(i);i++;}
				b = actionMessage.substring(i+1,actionMessage.length());
				val_a = Integer.parseInt(a);
				val_b = Integer.parseInt(b);
				//Main Work
	
					Exchange var3 = this.searchNode(val_a);
					    String str1 = actionMessage+": ";
						String str2 = Integer.toString(var3.child(val_b).data);
						str1 = str1+str2;
					    return str1;
				
				
			case 15 :
				a = actionMessage.substring(i+1,actionMessage.length());
				val_a = Integer.parseInt(a);
				//Main Work
	
					Exchange base = getNextNode(val_a);
					MobilePhone var4 = base.residentSet().search(val_a);
					var4.switchOff();
					
			
				break;
						
			case 19 :
				a = actionMessage.substring(i+1,actionMessage.length());
				val_a = Integer.parseInt(a);
				//Main Work
			
					Exchange var5 = this.searchNode(val_a);
					String str3 = actionMessage+": ";
					for(int j=0;j<var5.residentSet().size();j++){
		
						str3 = str3 + Integer.toString(var5.residentSet().getIdAt(j))+",";
					}
					str3 = str3.substring(0,str3.length()-1);
				return str3;
			
				
		}
		return "";
	}
	/*******************************************MAIN CHECKER FUNCTION*********************************/
	public static void main(String args []){
		RoutingMapTree T = new RoutingMapTree();
		
		System.out.println(T.performAction("addExchange 0 1"));
		System.out.println(T.performAction("addExchange 0 2"));
		System.out.println(T.performAction("addExchange 0 3"));
		System.out.println(T.performAction("queryNthChild 0 0"));
		System.out.println(T.performAction("queryNthChild 0 2"));
		System.out.println(T.performAction("addExchange 1 4"));
		System.out.println(T.performAction("addExchange 1 5"));
		System.out.println(T.performAction("addExchange 2 6"));
		System.out.println(T.performAction("addExchange 2 7"));
		System.out.println(T.performAction("addExchange 2 8"));
		System.out.println(T.performAction("addExchange 3 9"));
		System.out.println(T.performAction("queryNthChild 2 0"));
		System.out.println(T.performAction("queryNthChild 3 0"));
		System.out.println(T.performAction("switchOnMobile 989 4"));
		System.out.println(T.performAction("switchOnMobile 876 4"));
		System.out.println(T.performAction("queryMobilePhoneSet 4"));
		System.out.println(T.performAction("queryMobilePhoneSet 1"));
		System.out.println(T.performAction("switchOnMobile 54 5"));
		System.out.println(T.performAction("queryMobilePhoneSet 1"));
		System.out.println(T.performAction("switchOffMobile 656"));
		System.out.println(T.performAction("queryMobilePhoneSet 1"));
		System.out.println(T.performAction("switchOnMobile 213 6"));
		System.out.println(T.performAction("switchOnMobile 568 7"));
		System.out.println(T.performAction("switchOnMobile 897 8"));
		System.out.println(T.performAction("switchOnMobile 295 8"));
		System.out.println(T.performAction("switchOnMobile 346 9"));
		System.out.println(T.performAction("queryMobilePhoneSet 0"));
	}
			
}
	
			

// Linked List For MopbilePhone ***********************************************************************************************************
class LinkedList {
	Node root;
	int size;
	
	public LinkedList() {
		root = new Node();
		size = 0;
	}
	
	
	public void setSize(int s) {
		this.size = s;
	}
	
	public MobilePhone get(int i){
		Node thisNode = this.root;
		for(int j = 0; j<i;j++){
			thisNode = thisNode.getNextNode();
		}
		return thisNode.get();
	}
	
	public int size() {
		return this.size;
	}
	
	public Node add(MobilePhone data) {
		Node newNode = new Node(data, root);
		this.root = newNode;
		this.size++;
		return newNode;
	}
	
	public boolean contains(MobilePhone a) {
		Node thisNode = this.root;
		
		while (thisNode != null) {
			if (thisNode.get() == a)
				return true;
			thisNode = thisNode.getNextNode();
		}
		return false;
	}
	
	public boolean remove(MobilePhone data) {
		Node thisNode = this.root;
		Node prevNode = null;
		
		while (thisNode != null) {
			if (thisNode.get() == data) {
				if (prevNode != null)
					prevNode.setNextNode(thisNode.getNextNode());
				else
					this.root = null;
				this.setSize(this.size()-1);
				return true;
			}
			prevNode = thisNode;
			thisNode = thisNode.getNextNode();
		}
		return false;
	}
	
	// Node class
	private class Node {
		private Node nextNode;
		private MobilePhone data;

		// 0-arg constructor, 1-arg constructor, 2-arg constructor
		private Node() { }
		
		private Node(MobilePhone val) {
			data = val;
		}
		
		private Node(MobilePhone val, Node next) {
			data = val;
			nextNode = next;
		}
		
		private void setData(MobilePhone val) {
			this.data = val;
		}
		
		private MobilePhone get() {
			return this.data;
		}
		
		private void setNextNode(Node n) {
			this.nextNode = n;
		}
		
		private Node getNextNode() {
			return this.nextNode;
		}
	}
}
//Myset*******************************************************************************************************************
class Myset{
	LinkedList LL;
	
	//Constructor
	Myset(){
		LL = new LinkedList();
	}
	
	
		
//IsEmpty(): returns true if the set is empty
	public boolean IsEmpty(){ 
		if(LL.size() == 0){ return true;}
		else{ return false;}
	}
	//IsMember(Object o) : Returns true if o is in the set, false otherwise.
	public boolean IsMember(MobilePhone o){ return LL.contains(o);}
	
	//Insert(Object o): Inserts o into the set.
	public void Insert(MobilePhone o){ LL.add(o);}
	
	//Delete(Object o): Deletes o from the set, throws exception if o is not in the set
	public void Delete(MobilePhone o){ LL.remove(o);}

	//getAt(int i) : Return Element of Myset at address i.
	public MobilePhone getAt(int i){return LL.get(i); }
	//Size : Return size of Myset.
	public int size(){ return LL.size();}
	
	//Union(Myset a): Returns a set which is the union of the current set with the set a.
	public Myset Union(Myset a){ 
		int i;
		Myset Uset = new Myset();
		for( i=0; i<a.size();i++){
			if(!this.IsMember(a.getAt(i))){
				Uset.Insert(a.getAt(i));
			}
		}
		for(i=0; i<this.size(); i++){
			Uset.Insert(this.getAt(i));
		}
		return Uset;
	}
	
	//Intersection(Myset a): Returns a set which is the intersection of the current set with the set a.
	public Myset Intersection(Myset a){
		int i;
		Myset Iset = new Myset();
		for(i = 0; i< this.size(); i++){
			if(a.IsMember(this.getAt(i))){
				Iset.Insert(this.getAt(i));
			}
			else{}
		}
		return Iset;
	}
	
			
}
//MobilePhone*********************************************************************************************************
class MobilePhone{
	Exchange loc;
	int state = 0;
	int data;
	//Constructor
	MobilePhone(int number){
		 data = number;
	}
	
	
	//number(): returns the id of the mobile phone.
	public int number(){ return data;}
	//status(): returns the status of the phone, i.e.switched on or switched off
	public boolean status(){ 
		if(state == 1){return true;}
		else{return false;}
	}
	//switchOn(): Changes the status to switched on.
	public void switchOn(){ state = 1;}
	//switchOff(): Changes the status to switched off.
	public void switchOff(){ state = 0;}
	/*location(): returns the base station with which 
	the phone is registered if the phone is switched on and an exception
	if the phone is off.*/
	public Exchange location(){
		try{
		if(state == 0){ throw new MyException();}
		
		else{return loc;}
		}
		catch(MyException ex){System.out.println("Error : MobilePhone is switchOff.");}
		Exchange a = new Exchange(-1);
		return a;
	}
}
//MobilePhoneSet*********************************************************************************************************
class MobilePhoneSet{
	
	Myset FirstMobile;
	//class MobilePhoneSet stores MobilePhone objects in a Myset.
	MobilePhoneSet(){
		FirstMobile = new Myset();
	}
	//size() :
	public int size() { return FirstMobile.size();}
	//add(MobilePhone a) : 
	public void add(MobilePhone a){ FirstMobile.Insert(a);}
	//getIdAt(int i) : 
	public int getIdAt(int i){return FirstMobile.getAt(i).number();}
	//getAt(int i) : 
	public MobilePhone getAt(int i){return FirstMobile.getAt(i);}
	//delete(MobilePhone a) :
	public void delete(MobilePhone a) { FirstMobile.Delete(a);}
	//isMember() :
	public boolean IsMember(MobilePhone a){return FirstMobile.IsMember(a);} 
	//search(int id) :
	public MobilePhone search(int id){
		for(int i=0; i<this.size(); i++){
			if(id == this.getIdAt(i)){return this.getAt(i);}
		}
		try{
			throw new MyException();
		}
		catch(MyException ex){System.out.println("Error : MobilePhone not found in residentSet.");}
		MobilePhone anil = new MobilePhone(0);
		return anil;
	}
	//Union(MobilePhoneSet a) : 
	public MobilePhoneSet Union(MobilePhoneSet a){
		MobilePhoneSet Uset = new MobilePhoneSet();
		Uset.FirstMobile = this.FirstMobile.Union(a.FirstMobile);
		return Uset;
	}
	
}
//Exchange**************************************************************************************************************
class Exchange{
	
	int data;
	Exchange parent;
	ExchangeList children = new ExchangeList();
	MobilePhoneSet MobList = new MobilePhoneSet();
	//Constructor
	Exchange(int number){
		this.data = number;
		this.parent = null;
	}
	//setChild(Exchange a) : set current node as child of a.
	public void setChild(Exchange a){
		a.parent = this;
		children.add(a);
	}
	//parent() : Return parent of node.
	public Exchange parent(){ return parent;}
	//numChildren : Return number of children of node.
	public int numChildren(){ return children.size();}
	//child(int i) : Return ith child of node.
	public Exchange child(int i){ 
		if(i>=this.numChildren()){
			try{
				throw new MyException();
			}
			catch(MyException ex){System.out.println("Error : Index exceed no. of children.");}
		}
		else{return children.getAt(i);}
	
	Exchange y = new Exchange(0);
	return y;
	}
	//isRoot() : return 1 if node is root.
	public boolean isRoot(){
		if(this.parent() == null){return true;}
		else{return false;}
	}
	//subtree(int i) : return ith subtree
	public RoutingMapTree subtree(int i){
		RoutingMapTree T = new RoutingMapTree();
		T.node = this.child(i);
		return T;
	}
	
	//residentset() : Return the mobile phone set of current node.
	public MobilePhoneSet residentSet(){ 
		if(this.numChildren() == 0){ return this.MobList;}
		else{
				MobilePhoneSet TotalMobList = new MobilePhoneSet();
				for(int i=0;i<this.numChildren();i++){
					TotalMobList  = TotalMobList.Union(this.child(i).residentSet());
				}
				return TotalMobList;
			}
	}
		
	
}
//ExchangeList***********************************************************************************************************
class ExchangeList{
	
	Linked_List List;
	//Constructor
	ExchangeList(){
		List = new Linked_List();
	}
	//size : Return no. of Exchange node in list.
	public int size(){ return List.size();}
	//getAt(int i) : Return data of ith node.
	public Exchange getAt(int i){ return List.get(i);}
	//add(Exchange a) : add a in the List.
	public void add(Exchange a){ List.add(a);}
		
}
//MyException*********************************************************************************************************************
// A Class that represents use-defined expception 
class MyException extends Exception 
{ 
  
}
//Linked List for Exchange*********************************************************************************************
class Linked_List {
	Node root;
	int size;
	
	public Linked_List() {
		root = new Node();
		size = 0;
	}
	
	
	public void setSize(int s) {
		this.size = s;
	}
	
	public Exchange get(int i){
		Node thisNode = this.root;
		for(int j = 0; j<i;j++){
			thisNode = thisNode.getNextNode();
		}
		return thisNode.get();
	}
	
	public int size() {
		return this.size;
	}
	
	public Node add(Exchange data) {
		Node newNode = new Node(data, root);
		this.root = newNode;
		this.size++;
		return newNode;
	}
	
	public boolean contains(Exchange a) {
		Node thisNode = this.root;
		
		while (thisNode != null) {
			if (thisNode.get() == a)
				return true;
			thisNode = thisNode.getNextNode();
		}
		return false;
	}
	
	public boolean remove(Exchange data) {
		Node thisNode = this.root;
		Node prevNode = null;
		
		while (thisNode != null) {
			if (thisNode.get() == data) {
				if (prevNode != null)
					prevNode.setNextNode(thisNode.getNextNode());
				else
					this.root = null;
				this.setSize(this.size()-1);
				return true;
			}
			prevNode = thisNode;
			thisNode = thisNode.getNextNode();
		}
		return false;
	}
	
	// Node class
	private class Node {
		private Node nextNode;
		private Exchange data;

		// 0-arg constructor, 1-arg constructor, 2-arg constructor
		private Node() { }
		
		private Node(Exchange val) {
			data = val;
		}
		
		private Node(Exchange val, Node next) {
			data = val;
			nextNode = next;
		}
		
		private void setData(Exchange val) {
			this.data = val;
		}
		
		private Exchange get() {
			return this.data;
		}
		
		private void setNextNode(Node n) {
			this.nextNode = n;
		}
		
		private Node getNextNode() {
			return this.nextNode;
		}
	}
}
		
	
	
			
	
	
	
	

		
	