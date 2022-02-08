
  design for question 2
  ----------------------
  
  new_node(data)
		T_node temp

		allocate space for temp having size equal to size of structure
		
		if(temp==NULL)
			print(ERROR creating a new node)
			exit
		
		temp.key1<-k
		temp.key2<- -1
		temp.left<-NULL
		temp.right<-NULL
		temp.middle<-NULL
		return temp
  
  
  insert(T,data)
	  
		z <- new_node(data) // util function creates a new node of tree

		y <- NULL
		x <- T.root

		do while(x!=NULL)
			y <- x
			
			do if(x->key2==-1)
			if(x->key1>data)
				int temp_var <- x->key1
				x->key2 <-  temp_var
				x->key1 <- data
			
			else
				x->key2 <- data

				return
			
			
			do if (z.key1 < x.key1)
				x <- x.left

			Else
				do if(z.key1 > x.key1 and z.key1 < x.key2)
					x <- x.middle

			Else 
				x <- x.right

		do if y==NULL
			T.root <- z

		else 
			do if(z.key1 < y.key1)
				y.left <- z

			do if(z.key1 > y.key1 and z.key1 < y.key2)
				y.middle <- z
			
			else
				y.right <- z
		
	find_height(root)

		do if(root.left!=NULL or root.right!=NULL or root.middle!=NULL)

			 lheight<-0
			 rheight<-0
			 mheight <-0
			do if(root.right!=NULL)
				rheight<-find_height(root.right)
			
			do if(root.left!=NULL)
				lheight<-find_height(root.left)

			do if(root.middle!=NULL)
				mheight<-find_height(root.middle)
			
			max_val <- max(lheight,mheight,rheight) // maximum value 
			
			max_val <- max_val+1
			return max_val

		

		return 0
	





	print_middle_heavy_util(T_root)
		 do if T_root !=NULL
				
			
			print_middle_heavy_util(T_root.left)
			print_middle_heavy_util(T_root.middle)
			print_middle_heavy_util(T_root.right)

			height_left=find_height(T_root.left)
			height_middle=find_height(T_root.middle)
			height_right=find_height(T_root.right)
			
			do if height_middle>height_left and height_middle>height_right
				do if T_root.key2!=-1
				 print(T_root.key1 , T_root.key2)
				else
					print(T_root.key1)


	print_middle_heavy(T)
		PREORDER_util(T.root)

	



   

