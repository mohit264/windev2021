# Use case
1. By taking help of CoCreateInstance Client requests ISum / ISubtract (Outer components) or Client have already requested ISum and requesting ISubtract or vice-versa.
2. Client request IMultiplication/IDivision(Inner Components) using ISum/ISubrtaraction (Outer)
3. Client request IDivision using IMultiplication or vice-versa. (Requesting Inner Interface using other Inner interface)
4. Suppose if client received ISum, client requested IMultiplication/IDivision and then requesting ISubratraction (Requesting Outer from Inner)

> In all above cases client header files only have CLSID_SumSubtract and doesn't know about any Inners

5.  Here some other clients may demand IMultiplication/IDvision (Directly from Inner) using CLSID_MultiplicationDivision (and not CLSID_SumSubtract)
6.  Requesting IDivision from above IMultiplication
7.  Client requesting IUnknown from outer components (ISum/ISubtract)
8.  Client requesting IUnknwon from inner components (IMultiplication/IDivision)
