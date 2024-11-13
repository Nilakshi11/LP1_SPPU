from xmlrpc.client import ServerProxy
proxy=ServerProxy("http://localhost:8000")

while(True):
    ch=int(input("\n1.Cube\n2.Factorial\n3.Exit\nEnter the Choice:"))
    if(ch==1):
        no=int(input("Enter the Number: "))
        print("Cube is ",proxy.cube_rpc(no))
    elif ch==2:
        no=int(input("Enter the Number: "))
        print("Factorial is ",proxy.factorial_rpc(no))
    elif ch==3:
        break
    else:
        print("Invalid Choice...")