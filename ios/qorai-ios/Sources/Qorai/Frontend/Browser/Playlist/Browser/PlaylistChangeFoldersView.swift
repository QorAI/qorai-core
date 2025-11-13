// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiStrings
import Data
import DesignSystem
import Foundation
import Introspect
import SwiftUI

struct PlaylistChangeFoldersView: View {
  var item: PlaylistItem

  @State private var selectedFolderID: PlaylistFolder.ID
  private var initialSelectedFolderID: PlaylistFolder.ID
  @FetchRequest(
    entity: PlaylistFolder.entity(),
    sortDescriptors: [
      NSSortDescriptor(keyPath: \PlaylistFolder.order, ascending: true),
      NSSortDescriptor(keyPath: \PlaylistFolder.dateAdded, ascending: false),
    ]
  ) private var folders: FetchedResults<PlaylistFolder>
  @Environment(\.presentationMode) @Binding private var presentationMode
  @ScaledMetric private var iconSize: CGFloat = 32

  init(item: PlaylistItem) {
    self.item = item
    self._selectedFolderID = State(wrappedValue: item.playlistFolder!.id)
    self.initialSelectedFolderID = item.playlistFolder!.id
  }

  @State private var isNewFolderActive: Bool = false

  var sortedFolders: [PlaylistFolder] {
    folders.sorted(by: { first, second in first.id == initialSelectedFolderID })
  }

  var body: some View {
    ScrollView(.vertical) {
      LazyVStack(spacing: 0) {
        ForEach(sortedFolders) { folder in
          Button {
            selectedFolderID = folder.id
          } label: {
            HStack {
              Image(qoraiSystemName: "qora.folder.open")
                .foregroundColor(
                  Color(folder.id == selectedFolderID ? .qoraiBlurpleTint : .qoraiLabel)
                )
                .frame(width: iconSize)
              VStack(alignment: .leading) {
                Text(folder.title ?? "")
                  .foregroundColor(Color(.qoraiLabel))
                Text(folderCountLabel(folder.playlistItems?.count ?? 0))
                  .foregroundColor(Color(.secondaryQoraiLabel))
                  .font(.subheadline)
              }
              Spacer()
              if folder.id == selectedFolderID {
                Image(qoraiSystemName: "qora.check.normal")
                  .foregroundStyle(Color(.qoraiBlurpleTint))
              }
            }
            .padding(.horizontal)
            .padding(.vertical, 12)
          }
          if folder.id != sortedFolders.last?.id {
            Divider()
              .padding(.horizontal)
          }
        }
      }
    }
    .background(Color(.qoraiBackground).ignoresSafeArea())
    .navigationTitle(Strings.PlaylistFolders.playlistChangeFoldersTitle)
    .navigationBarTitleDisplayMode(.inline)
    .toolbar {
      ToolbarItemGroup(placement: .confirmationAction) {
        Button(Strings.done) {
          presentationMode.dismiss()
        }
      }
      ToolbarItemGroup(placement: .bottomBar) {
        Button {
          isNewFolderActive = true
        } label: {
          Text(Strings.PlaylistFolders.playlistNewFolderButtonTitle)
            .font(.subheadline.weight(.semibold))
            .foregroundColor(Color(.qoraiBlurpleTint))
            .frame(maxWidth: .infinity)
            .padding(.vertical, 2)
        }
        .buttonStyle(QoraiOutlineButtonStyle(size: .normal))
      }
    }
    .onChange(of: selectedFolderID) { newValue in
      guard let folder = folders.first(where: { $0.id == newValue }) else { return }
      PlaylistItem.moveItems(items: [item.objectID], to: folder.uuid)
    }
    .background {
      NavigationLink(isActive: $isNewFolderActive) {
        CreateFolderView(item: item, selectedFolderID: $selectedFolderID)
      } label: {
        EmptyView()
      }
    }
  }

  private func folderCountLabel(_ count: Int) -> String {
    String.localizedStringWithFormat(
      count == 1
        ? Strings.PlayList.folderItemCountSingular : Strings.PlayList.folderItemCountPlural,
      count
    )
  }
}

private struct CreateFolderView: View {
  var item: PlaylistItem
  @Binding var selectedFolderID: PlaylistFolder.ID

  @FocusState private var focused: Bool
  @State private var title: String = ""
  @Environment(\.dismiss) var dismiss

  private func saveTapped() {
    if title.isEmpty { return }
    PlaylistFolder.addFolder(title: title) { uuid in
      PlaylistItem.moveItems(items: [item.objectID], to: uuid)
      selectedFolderID = uuid
      dismiss()
    }
  }

  var body: some View {
    ScrollView(.vertical) {
      VStack(alignment: .leading) {
        Text(Strings.PlaylistFolders.playlistCreateFolderTextFieldLabel)
          .font(.subheadline)
        TextField(Strings.PlaylistFolders.playlistCreateFolderTextFieldPlaceholder, text: $title)
          .focused($focused)
          .onSubmit {
            saveTapped()
          }
          .onAppear {
            DispatchQueue.main.async {
              focused = true
            }
          }
          .padding(.horizontal, 16)
          .padding(.vertical, 8)
          .background(
            Color(.secondaryQoraiBackground)
          )
          .containerShape(RoundedRectangle(cornerRadius: 8, style: .continuous))
      }
      .padding()
    }
    .background(Color(.qoraiBackground).ignoresSafeArea())
    .navigationTitle(Strings.PlaylistFolders.playlistNewFolderScreenTitle)
    .navigationBarTitleDisplayMode(.inline)
    .toolbar {
      ToolbarItem(placement: .confirmationAction) {
        Button(Strings.PlaylistFolders.playlistCreateNewFolderButtonTitle) {
          saveTapped()
        }
        .disabled(title.isEmpty)
      }
    }
  }
}

struct PlaylistChangeFoldersContainerView: View {
  var item: PlaylistItem

  var body: some View {
    NavigationView {
      PlaylistChangeFoldersView(item: item)
    }
    .navigationViewStyle(.stack)
    .introspectNavigationController { nc in
      DispatchQueue.main.async {
        let appearance = UIToolbarAppearance()
        appearance.configureWithTransparentBackground()
        appearance.backgroundColor = .qoraiBackground
        nc.toolbar.standardAppearance = appearance
        nc.toolbar.scrollEdgeAppearance = appearance
        nc.toolbar.compactAppearance = appearance
      }
    }
    .environment(\.managedObjectContext, DataController.swiftUIContext)
  }
}

class PlaylistChangeFoldersViewController: UIHostingController<PlaylistChangeFoldersContainerView> {
  init(item: PlaylistItem) {
    super.init(rootView: PlaylistChangeFoldersContainerView(item: item))
    sheetPresentationController?.prefersGrabberVisible = true
    sheetPresentationController?.prefersEdgeAttachedInCompactHeight = true
    sheetPresentationController?.detents = [.medium(), .large()]
  }

  @available(*, unavailable)
  required init(coder: NSCoder) {
    fatalError()
  }
}
