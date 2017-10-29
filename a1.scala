object BinarySearch
{
def binsearch(nos:Array[Int],srno:Int,l:Int,r:Int) :Int =
{
	var mid:Int=(l+r)/2
	if(l>r)
	{	return -1}
	else if(nos(mid)==srno)
	{	return mid}
	else if(nos(mid)>srno)
	{	binsearch(nos,srno,l,mid-1)}
	else 
	{	binsearch(nos,srno,mid+1,r)}
}
def binsearchnon(nos:Array[Int],srno:Int,l:Int,r:Int) :Int =
{
	var low:Int=l
	var high:Int=r
	var mid:Int=(l+r)/2
	while(low<=high)
	{
		mid=(low+high)/2
		if(nos(mid)==srno)
		{ return mid}
		else if(nos(mid)>srno)
		{	high=mid-1}
		else 
		{	low=mid+1}
	}
	return -1
}

def main(args:Array[String])
{
	println("Enter count")
	var n:Int=Console.readInt
	println("Enter nos.")
	var nos= new Array[Int](n)

	for(i <- 0 to n-1 )
	{	nos(i)=Console.readInt}

	nos=nos.sorted
	println("enter no.")
	var srno:Int=Console.readInt

	var pos:Int=binsearchnon(nos,srno,0,n-1)

	if(pos == -1)
	{
		println("berrr")
	}
	else 
	{
		println("index is"+(pos+1)+" lol")
	}
}
}






