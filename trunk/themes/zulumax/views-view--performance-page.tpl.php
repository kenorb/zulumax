<?php drupal_add_css (path_to_theme () . '/css/style-main.css'); ?>
<?php drupal_add_css (path_to_theme () . '/css/style-performance-page.css'); ?>

<table class="performance-page-table" cellpadding="0" cellspacing="0" border="0">
	<thead>
		<tr>
			<?php echo get_next_sort_link ($view, 'Rank',			'field_ranking_value',			'ASC'); ?>
			<?php echo get_next_sort_link ($view, 'Title',			'title',						'ASC'); ?>
			<?php echo get_next_sort_link ($view, 'Pips',			'field_profit_value',			'DESC'); ?>
			<?php echo get_next_sort_link ($view, 'Trades',			'field_trades_value',			'DESC'); ?>
			<?php echo get_next_sort_link ($view, 'Avg Pips',		'field_avg_pips_trade_value',	'DESC'); ?>
			<?php echo get_next_sort_link ($view, 'Win',			'field_winning_trades_value',	'DESC'); ?>
			<?php echo get_next_sort_link ($view, 'Avg Trade Time',	'field_avg_trade_time_value',	'DESC', '<th style="%th-styles">%link<br/><div class="mini">in hours</div></th>'); ?>
			<?php echo get_next_sort_link ($view, 'Weeks',			'field_running_weeks_value',	'DESC'); ?>
			<?php echo get_next_sort_link ($view, 'Max DD',			'field_max_drawdown_value',		'DESC'); ?>
			<?php echo get_next_sort_link ($view, 'Followers',		'field_followers_value',		'DESC'); ?>
		<tr>
	</thead>
	<?php foreach ($view -> result as $rowId => $row): ?>
		<tr>
			<td class="column-num performance-page-column-rank">
				<?php echo $row -> _field_data ['nid'] ['entity'] -> field_ranking ['und'] [0] ['value']; ?>
			</td>
			<td class="performance-page-column-sp">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[title]']; ?>
			</td>
			<td class="column-num performance-page-column-stat performance-page-column-stats-column-pips">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_profit]']; ?>
			</td>
			<td class="column-num performance-page-column-stat performance-page-column-stats-column-trades">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_trades]']; ?>
			</td>
			<td class="column-num performance-page-column-stat performance-page-column-stats-column-avg-pips">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_avg_pips_trade]']; ?>
			</td>
			<td class="column-num performance-page-column-stat performance-page-column-stats-column-win-trades">
				<?php echo number_format (
					100.0
					/ $row -> _field_data ['nid'] ['entity'] -> field_trades ['und'] [0] ['value']
					* $row -> _field_data ['nid'] ['entity'] -> field_winning_trades ['und'] [0] ['value']
					); ?> %
			</td>
			<td class="column-num performance-page-column-stat performance-page-column-stats-column-avg-trade-time">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_avg_trade_time]']; ?>
			</td>
			<td class="column-num performance-page-column-stat performance-page-column-stats-column-weeks">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_running_weeks]']; ?>
			</td>
			<td class="column-num performance-page-column-stat performance-page-column-stats-column-max-dd">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_max_drawdown]']; ?> %
			</td>
			<td class="column-num performance-page-column-stat performance-page-column-stats-column-followers">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_followers]']; ?>
			</td>
		</tr>
	<?php endforeach; ?>
</table>

<?php echo $pager; ?>
