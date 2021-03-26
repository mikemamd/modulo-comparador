(function($) {
  Drupal.behaviors.toComparator = {
    attach : function(context) {

      var tids = [];  
      $("div .compara").click(function() {
        var id = $(this).attr("id");
        if($(this).hasClass('activo')) {
          $(this).parent().parent().removeClass('selected');
          var pos = tids.indexOf(id);                 
          if (pos >= 0) {
            tids.splice(pos, 1);
          }
        }
        else{
          $(this).parent().parent().addClass('selected');
          if (tids.length <= 1) {
            tids.push(id);

          }
          else{
            $(this).toggleClass('activo');
          }
        }

        if (tids.length == 2) {
          $(".version:not(.selected)").addClass('disable');
        }else{
          $(".flex .version").removeClass('disable');
        }
      });

      $(".boton").click(function(e) {
        var modelo = Drupal.settings.toComparator;
        var versiones = Drupal.settings.versiones;

        if (tids.length == 2) {
          ga(function(tracker) {
            var clientId = tracker.get('clientId');
            var dataLayer = dataLayer || [];

            dataLayer.push({
              orderID: clientId,
              event: 'Compara',
              section: 'Comparador de Versiones',
              modelo: modelo,
              version1: versiones[tids[0]].version,
              version2: versiones[tids[1]].version
            });                 
          });

          var selectedVersions = {
            versionUno: versiones[tids[0]],
            versionDos: versiones[tids[1]],
          };
          var json_str2 = JSON.stringify(selectedVersions);
          $.cookie('comparadorVersiones', json_str2, { path: '/' });
        }
        else{
          e.preventDefault();
          alert('Selecciona 2 versiones para poder comparar');
        }
      });

    }
  };
})(jQuery);

