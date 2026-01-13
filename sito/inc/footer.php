<div class="footer">
 <footer>
  <?php
   $site = include("parsing.php");
  
   echo"<p>" . $site["footer"] . "</p>"
  ?>
 </footer>

 <script>
 document.addEventListener("DOMContentLoaded", () => 
 {
   const content = document.querySelector(".content");
   if(!content) return;

   // Ripristino scroll
   const saved = sessionStorage.getItem("contentScrollTop");
   if(saved !== null) 
   {
     requestAnimationFrame(() => 
     {
       content.scrollTop = parseInt(saved, 10);
       sessionStorage.removeItem("contentScrollTop");
     });
   }

   // Salvataggio scroll prima del submit (solo form dentro .content)
   content.querySelectorAll("form").forEach(form => 
   {
    form.addEventListener("submit", () => 
    {
    sessionStorage.setItem("contentScrollTop", content.scrollTop);
    });
   });
 });
 </script>

</div>