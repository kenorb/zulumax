index 0b9b620..9d7ec1d 100644
--- includes/FeedsConfigurable.inc
+++ includes/FeedsConfigurable.inc
@@ -146,7 +146,7 @@ abstract class FeedsConfigurable {
    */
   public function getConfig() {
     $defaults = $this->configDefaults();
-    return $this->config + $defaults;
+    return (array)$this->config + (array)$defaults;
   }
 
   /**
