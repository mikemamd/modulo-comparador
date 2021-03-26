<?php
/**
 * Implements hook_field_info()
 */
function comparator_field_info() {
  return array(
    'tecnica' => array(
      'label'             => t('tecnica'),
      'description'       => t('Field especificaciones tecnicas'),
      'default_widget'    => 'widget_tecnicas',
      'default_formatter' => 'format_tecnicas',
    ),
    'dimex' => array(
      'label'             => t('dimex'),
      'description'       => t('Field dimensiones exteriores'),
      'default_widget'    => 'widget_dimex',
      'default_formatter' => 'format_dimex',
    ),
    'dimin' => array(
      'label'             => t('dimin'),
      'description'       => t('Field dimensiones interiores'),
      'default_widget'    => 'widget_dimin',
      'default_formatter' => 'format_dimin',
    ),
    'peso_cap' => array(
      'label'             => t('peso y capacidades'),
      'description'       => t('Field peso y capacidades'),
      'default_widget'    => 'widget_peso',
      'default_formatter' => 'format_peso',
    ),
  );
}

/**
 * Implements hook_field_validate().
 */
function comparator_field_validate($obj_type, $object, $field, $instance, $langcode, &$items, &$errors) {
  foreach ($items as $delta => $item) {
    if ($item['value'] != '') {
      if ( empty($item['value'])) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
          'error'   => 'tecnica',
          'message' => t('el valor no puede quedar vacío'),
        );
      }//end if
    }//end if
  }//end foreach
}

/**
 * Implements hook_field_is_empty().
 */
function comparator_field_is_empty($item, $field) {
  if (empty($item['value'])) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Implements hook_field_formatter_info().
 */
function comparator_field_formatter_info() {
  return array(
    'format_tecnicas' => array(
      'label' => t('formato para field expecificaciones técnicas'),
      'field types' => array('tecnica'),
    ),
    'format_dimex' => array(
      'label' => t('formato para field dimensiones exteriores'),
      'field types' => array('dimex'),
    ),
    'format_dimin' => array(
      'label' => t('formato para field dimensiones interiores'),
      'field types' => array('dimin'),
    ),
    'format_peso' => array(
      'label' => t('formato para field peso y capacidades'),
      'field types' => array('peso_cap'),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function comparator_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($display['type']) {
    case 'format_tecnicas':
      $options = comparator_get_widget_options('comparador_tecnicas');
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#type'  => 'fieldset',
          '#title' => t('field especificaciones tecnicas')
        );
        if ($item['value']){
          $element[$delta]['value']['#markup'] = $item['value'];
        }//end if
        if ($item['tid_tec']){
          $element[$delta]['tid_tec']['#markup'] = $options[ $item['tid_tec'] ];
        }//end if
      }//end foreach
      break;
    case 'format_dimex':
      $options = comparator_get_widget_options('comparador_dimension_e');
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#type'  => 'fieldset',
          '#title' => t('field dimensiones exteriores')
        );
        if ($item['value']){
          $element[$delta]['value']['#markup'] = $item['value'];
        }//end if
        if ($item['tid_dimex']){
          $element[$delta]['tid_dimex']['#markup'] = $options[ $item['tid_dimex'] ];
        }//end if
      }//end foreach
      break;
    case 'format_dimin':
      $options = comparator_get_widget_options('comparador_dimension_i');
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#type'  => 'fieldset',
          '#title' => t('field dimensiones interiores')
        );
        if ($item['value']){
          $element[$delta]['value']['#markup'] = $item['value'];
        }//end if
        if ($item['tid_dimin']){
          $element[$delta]['tid_dimin']['#markup'] = $options[ $item['tid_dimin'] ];
        }//end if
      }//end foreach
      break;
    case 'format_peso':
      $options = comparator_get_widget_options('comparador_peso');
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#type'  => 'fieldset',
          '#title' => t('field peso y capacidades')
        );
        if ($item['value']){
          $element[$delta]['value']['#markup'] = $item['value'];
        }//end if
        if ($item['tid_peso']){
          $element[$delta]['tid_peso']['#markup'] = $options[ $item['tid_peso'] ];
        }//end if
      }//end foreach
      break;
  }//end switch

  return $element;
}

/**
 * Implements hook_field_widget_info().
 */
function comparator_field_widget_info() {
  return array(
    'widget_tecnicas' => array(
      'label'       => t('widget especificaciones tecnicas'),
      'field types' => array('tecnica')
    ),
    'widget_dimex' => array(
      'label'       => t('widget dimensiones exteriores'),
      'field types' => array('dimex')
    ),
    'widget_dimin' => array(
      'label'       => t('widget dimensiones interiores'),
      'field types' => array('dimin')
    ),
    'widget_peso' => array(
      'label'       => t('widget peso y capacidades'),
      'field types' => array('peso_cap')
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function comparator_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  switch ($instance['widget']['type']) {
    case 'widget_tecnicas':
      $options = comparator_get_widget_options('comparador_tecnicas');
      $element['tid_tec'] = array(
        '#type'          => 'select',
        '#title'         => t('Especificación Técnica'),
        '#description'   => t('Selecciona una especificación técnica'),
        '#options'       => $options,
        '#default_value' => isset($items[$delta]['tid_tec']) ? $items[$delta]['tid_tec'] : '',
        '#required'      => true,
      );
      $element['value'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Caracteristíca'),
        '#description'   => t('Ingresar caracteristíca de la especificación técnica'),
        '#default_value' => isset($items[$delta]['value']) ? $items[$delta]['value'] : '',
        '#required'      => $element['#required'],
      );
      break;
    case 'widget_dimex':
      $options = comparator_get_widget_options('comparador_dimension_e');
      $element['tid_dimex'] = array(
        '#type'          => 'select',
        '#title'         => t('Dimensión Exterior'),
        '#description'   => t('Selecciona una dimensión exterior'),
        '#options'       => $options,
        '#default_value' => isset($items[$delta]['tid_dimex']) ? $items[$delta]['tid_dimex'] : '',
        '#required'      => true,
      );
      $element['value'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Caracteristíca'),
        '#description'   => t('Ingresar caracteristíca de la dimensión exterior'),
        '#default_value' => isset($items[$delta]['value']) ? $items[$delta]['value'] : '',
        '#required'      => $element['#required'],
      );
      break;
    case 'widget_dimin':
      $options = comparator_get_widget_options('comparador_dimension_i');
      $element['tid_dimin'] = array(
        '#type'          => 'select',
        '#title'         => t('Dimensión Interior'),
        '#description'   => t('Selecciona una dimensión interior'),
        '#options'       => $options,
        '#default_value' => isset($items[$delta]['tid_dimin']) ? $items[$delta]['tid_dimin'] : '',
        '#required'      => true,
      );
      $element['value'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Caracteristíca'),
        '#description'   => t('Ingresar caracteristíca de la dimensión interior'),
        '#default_value' => isset($items[$delta]['value']) ? $items[$delta]['value'] : '',
        '#required'      => $element['#required'],
      );
      break;
    case 'widget_peso':
      $options = comparator_get_widget_options('comparador_peso');
      $element['tid_peso'] = array(
        '#type'          => 'select',
        '#title'         => t('Peso y Capacidades'),
        '#description'   => t('Selecciona un Peso/Capacidad'),
        '#options'       => $options,
        '#default_value' => isset($items[$delta]['tid_peso']) ? $items[$delta]['tid_peso'] : '',
        '#required'      => true,
      );
      $element['value'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Caracteristíca'),
        '#description'   => t('Ingresar caracteristíca del Peso/Capacidad'),
        '#default_value' => isset($items[$delta]['value']) ? $items[$delta]['value'] : '',
        '#required'      => $element['#required'],
      );
      break;
  } //end switch
  return $element;
}

/**
 * Get the list options to fields
 * @param (string) $vocabulary
 * @return (array)
 */
function comparator_get_widget_options($vocabulary) {
  $result = $terms = array();
  $result[0] = '- Seleccionar -';
  $voc   = taxonomy_vocabulary_machine_name_load($vocabulary);
  $terms = taxonomy_get_tree($voc->vid);
  if(count($terms)){
    foreach($terms as $term){
      $result[$term->tid] = $term->name;
    }//end foreach
  }//end if

  return $result;
}
