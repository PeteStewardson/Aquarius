/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Name        : Aquarius.cpp
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Dec 30, 2012
 *
 * Copyright © 2012 Georgi Todorov  <terahz@geodar.com>
 */

#include "Aquarius.h"

Aquarius::Aquarius(const Wt::WEnvironment& env) :
		Wt::WApplication(env) {
	pl = new PluginLoader();
	tabs = new Wt::WTabWidget(root());
	tabs->currentChanged().connect(this, &Aquarius::updateTab);
	timer = new Wt::WTimer();
	timer->setInterval(30000);
	timer->timeout().connect(this, &Aquarius::refresh);
	timer->start();
}

Aquarius::~Aquarius() {
	delete(pl);
}

void Aquarius::load() {
	Wt::WContainerWidget * summaryContainer = new Wt::WContainerWidget();
	int pluginCount = 0;
	unsigned int ii = 0;
	printf("Loading Plugins (Aquarius::load)\n");
	tabs->addTab(summaryContainer, "Summary");
	if (pl) {
		pluginCount = pl->loadPlugins("./");
		if (pluginCount > 0) {
			for (ii = 0; ii < pl->getPlugins().size(); ii++) {
				AquariusPlugin * plugin = pl->getPlugins()[ii];
				plugins.push_back(plugin);
				tabs->addTab(plugin->getTab(), plugin->getName());
				summaryContainer->addWidget(plugin->getSummary());

			}
		} else {
			summaryContainer->addWidget(
					new Wt::WText(
							"<h2> Awww, you don't have any plugins installed</h2>"));
		}
	}
	tabs->setCurrentIndex(0);

}

void Aquarius::updateTab(int tab) {
	if (tab > 0) {
		printf("Updating tab %d %s\n", tab,
				plugins[tab - 1]->getName().c_str());
		plugins[tab - 1]->refresh();
	}
}

void Aquarius::refresh(){
	unsigned int ii;
	for (ii = 0; ii < plugins.size(); ii++){
		plugins[ii]->refresh();
	}
	std::cout << "Refresh being called" << std::endl;
	printf("Refresh Called/n");
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env) {
	Aquarius *aq = new Aquarius(env);
	aq->setCssTheme("polished");
	aq->load();
	aq->enableUpdates(true);

	return aq;
}

int main(int argc, char **argv) {
	printf("Starting Aquarius/n");
	return Wt::WRun(argc, argv, &createApplication);
}
