<?php

/**
 * @file
 * Menu related functions.
 */

use Drupal\civictheme\CivicthemeConstants;

/**
 * Preprocess for footer menu block.
 */
function _civictheme_preprocess_block__civictheme_footer_menu(&$variables) {
  if (isset($variables['elements']['#base_plugin_id']) && $variables['base_plugin_id'] != 'menu_block') {
    return;
  }

  $menu_name = strtr($variables['elements']['#derivative_plugin_id'], '-', '_');
  if ($menu_name == 'civictheme_footer') {
    // Set menu theme as per footer theme.
    $variables['theme'] = civictheme_get_theme_config_manager()->load('components.footer.theme', CivicthemeConstants::FOOTER_THEME_DEFAULT);
    $variables['items'] = $variables['content']['#items'] ?? [];
    $variables['title'] = $variables['configuration']['label_display'] ? $variables['configuration']['label'] : '';

    _civictheme_preprocess_menu_items($variables['items']);
  }
}

/**
 * Add required element for external link.
 */
function _civictheme_preprocess_menu_items(&$items) {
  foreach ($items as &$item) {
    $item += [
      'is_new_window' => $item['url']->isExternal(),
      'is_external' => $item['url']->isExternal(),
    ];

    if (empty($item['original_link']->getPluginDefinition()['expanded'])) {
      $item['below'] = [];
      $item['is_expanded'] = FALSE;
    }

    if (count($item['below'])) {
      _civictheme_preprocess_menu_items($item['below']);
    }
  }
}

/**
 * Preprocess for primary navigation menu block.
 */
function _civictheme_preprocess_block__navigation(&$variables) {
  if (isset($variables['elements']['#base_plugin_id']) && $variables['base_plugin_id'] != 'menu_block') {
    return;
  }

  $menu_name = strtr($variables['elements']['#derivative_plugin_id'], '-', '_');

  if ($menu_name == 'civictheme_primary_navigation' || $menu_name == 'civictheme_secondary_navigation') {
    $key = substr($menu_name, strlen('civictheme_'));
    // Set menu theme as per footer theme.
    $variables['theme'] = civictheme_get_theme_config_manager()->load('components.header.theme', CivicthemeConstants::HEADER_THEME_DEFAULT);
    $variables['items'] = $variables['content']['#items'] ?? [];
    $variables['dropdown'] = civictheme_get_theme_config_manager()->load("components.navigation.$key.dropdown", $menu_name == 'civictheme_primary_navigation' ? CivicthemeConstants::NAVIGATION_DROPDOWN_DRAWER : CivicthemeConstants::NAVIGATION_DROPDOWN_DROPDOWN);
    $variables['dropdown_columns'] = civictheme_get_theme_config_manager()->load("components.navigation.$key.dropdown_columns", 4);
    $variables['dropdown_columns_fill'] = civictheme_get_theme_config_manager()->load("components.navigation.$key.dropdown_columns_fill", FALSE);
    $variables['is_animated'] = civictheme_get_theme_config_manager()->load("components.navigation.$key.is_animated", FALSE);
    _civictheme_preprocess_menu_items($variables['items']);
  }
}
