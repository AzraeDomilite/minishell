 {
   if( $2 == "*" ) {
      if( f ) {
         print f
      }
      f = $1
   }
   else {
      f = ""
   }
}
