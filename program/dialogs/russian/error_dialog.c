яю 
 v o i d   P r o c e s s D i a l o g E v e n t ( )  
 {  
 	 r e f   N P C h a r ;  
 	 a r e f   L i n k ,   N e x t D i a g ;  
  
 	 D e l e t e A t t r i b u t e ( & D i a l o g , " L i n k s " ) ;  
  
 	 m a k e r e f ( N P C h a r , C h a r a c t e r R e f ) ;  
 	 m a k e a r e f ( L i n k ,   D i a l o g . L i n k s ) ;  
 	 m a k e a r e f ( N e x t D i a g ,   N P C h a r . D i a l o g ) ;  
  
 	 s w i t c h ( D i a l o g . C u r r e n t N o d e )  
 	 {  
 	 	 / /   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 80;>3  ?5@2K9  -   ?5@20O  2AB@5G0 
 	 	 c a s e   " F i r s t   t i m e " :  
 	 	 	  
 	 	 	 d i a l o g . t e x t   =   " E r r o r   o p e n i n g   d i a l o g   f i l e . " ;  
 	 	 	 i f ( C h e c k A t t r i b u t e ( C h a r a c t e r R e f ,   " D i a l o g . F i l e n a m e " ) )  
 	 	 	 {  
 	 	 	 	 d i a l o g . t e x t   =   " D i a l o g   f i l e   f o r   t h a t   c h a r a c t e r   "   +   C h a r a c t e r R e f . D i a l o g . F i l e n a m e   +   " ,   c o u l d   n o t   b e   o p e n e d . " ;  
 	 	 	 }  
 	 	 	 l i n k . l 1   =   " o k " ;  
 	 	 	 l i n k . l 1 . g o   =   " E x i t " ;  
 	 	 	 N e x t D i a g . T e m p N o d e   =   " F i r s t   t i m e " ;  
 	 	 b r e a k ;  
  
 	 	 c a s e   " E x i t " :  
 	 	 	 N e x t D i a g . C u r r e n t N o d e   =   N e x t D i a g . T e m p N o d e ;  
 	 	 	 D i a l o g E x i t ( ) ;  
 	 	 b r e a k ;  
 	 }  
 }  
 