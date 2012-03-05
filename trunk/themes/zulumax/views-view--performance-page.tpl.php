<?php drupal_add_css (path_to_theme () . '/css/style-performance-page.css'); ?>

<table class="performance-page-table" cellpadding="0" cellspacing="0" border="0">
	<?php foreach ($view -> result as $rowId => $row): ?>
		<tr>
			<td class="performance-page-column-rank">
				<?php echo $row -> _field_data ['nid'] ['entity'] -> field_ranking ['und'] [0] ['value']; ?>
			</td>
			<td class="performance-page-column-sp">
				<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[title]']; ?>
			</td>
			<td class="performance-page-column-stats">
				<table cellpadding="0" cellspacing="0" border="0">
					<thead>
						<tr>
							<th>Pips</th>
							<th>Trades</th>
							<th>Avg Pips</th>
							<th>Win %</th>
							<th>Avg Trade Time</th>
							<th>Weeks</th>
							<th>Max DD%</th>
							<th>Followers</th>
						</tr>
					</thead>
					<tbody>
						<tr>
							<td class="performance-page-column-stats-column-pips">
							</td>
							<td class="performance-page-column-stats-column-trades">
								<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_trades]']; ?>
							</td>
							<td class="performance-page-column-stats-column-avg-pips">
								<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_avg_pips_trade]']; ?>
							</td>
							<td class="performance-page-column-stats-column-win-trades">
								<?php echo number_format (
									100.0
									/ $row -> _field_data ['nid'] ['entity'] -> field_trades ['und'] [0] ['value']
									* $row -> _field_data ['nid'] ['entity'] -> field_winning_trades ['und'] [0] ['value']
									); ?>
							</td>
							<td class="performance-page-column-stats-column-avg-trade-time">
								<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_avg_trade_time]']; ?>
							</td>
							<td class="performance-page-column-stats-column-weeks">
								<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_running_weeks]']; ?>
							</td>
							<td class="performance-page-column-stats-column-max-dd">
								<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_max_drawdown]']; ?>
							</td>
							<td class="performance-page-column-stats-column-followers">
								<?php echo $view -> style_plugin -> row_tokens [$rowId] ['[field_followers]']; ?>
							</td>
						</tr>
					</tbody>
				</table>
			</td>
		</tr>
	<?php endforeach; ?>
</table>
