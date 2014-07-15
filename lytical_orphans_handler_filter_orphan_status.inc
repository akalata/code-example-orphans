<?php
/**
 * Filter by published status
 */
class lytical_orphans_handler_filter_orphan_status extends views_handler_filter {

  function query() {
    // build array of nodes WITH menu items
    $existing_links_query = "SELECT link_path FROM {menu_links} WHERE link_path LIKE 'node/%'";
    $existing_links_result = db_query($existing_links_query);
    $existing_links_nids = array();
    foreach ($existing_links_result as $row) {
      $path = explode('/',$row->link_path);
      if (is_numeric($path[1])) {
        $existing_links_nids[] = $path[1];
      }
    }
    $existing_links_nids = array_unique($existing_links_nids);

    // exclude these nids from the query
    $menu_nids = implode(', ',$existing_links_nids);
    $this->query->add_where($this->options['group'], 'node.nid', $existing_links_nids, 'NOT IN');

  }
}
