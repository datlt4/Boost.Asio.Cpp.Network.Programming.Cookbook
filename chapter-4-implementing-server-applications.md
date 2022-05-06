# Implementing Server Applications

## Introduction

- Máy chủ là một phần của ứng dụng phân tán cung cấp `Service` hoặc các `Service` được sử dụng bởi các phần khác của ứng dụng này — máy khách. Khách hàng giao tiếp với máy chủ để sử dụng các `Service` do nó cung cấp.

- Thông thường, một ứng dụng máy chủ đóng một vai trò thụ động trong quá trình giao tiếp giữa máy khách-máy chủ. Trong quá trình khởi động, một ứng dụng máy chủ gắn vào một cổng nổi tiếng cụ thể (nghĩa là, nó được các máy khách tiềm năng biết đến hoặc ít nhất nó có thể được các máy khách lấy trong thời gian chạy từ một số đăng ký nổi tiếng) trên máy chủ. Sau đó, nó chờ đợi một cách thụ động các yêu cầu đến cổng đó từ các máy khách. Khi yêu cầu đến, máy chủ xử lý nó (phục vụ) bằng cách thực hiện các hành động theo đặc điểm kỹ thuật của `Service` mà nó cung cấp.

- Tùy thuộc vào các `Service` mà máy chủ cụ thể cung cấp, việc xử lý yêu cầu có thể có ý nghĩa khác. Ví dụ, một máy chủ HTTP thường sẽ đọc nội dung của một tệp được chỉ định trong thông báo yêu cầu và gửi nó trở lại máy khách. Một máy chủ proxy sẽ chỉ chuyển hướng yêu cầu của khách hàng đến một máy chủ khác để xử lý thực tế (hoặc có thể cho một vòng chuyển hướng khác). Các máy chủ khác cụ thể hơn có thể cung cấp các `Service` thực hiện các phép tính phức tạp trên dữ liệu do máy khách cung cấp trong yêu cầu và trả lại kết quả của các phép tính đó cho máy khách.

- Không phải tất cả các máy chủ đều đóng vai trò thụ động. Một số ứng dụng máy chủ có thể gửi tin nhắn đến máy khách mà không cần đợi máy khách gửi yêu cầu trước. Thông thường, các máy chủ như vậy hoạt động như người thông báo và chúng thông báo cho khách hàng về một số sự kiện thú vị. Trong trường hợp này, các máy khách có thể không cần gửi bất kỳ dữ liệu nào đến máy chủ. Thay vào đó, họ thụ động chờ đợi thông báo từ máy chủ và sau khi nhận được thông báo, họ sẽ phản ứng tương ứng. Mô hình giao tiếp như vậy được gọi là giao tiếp kiểu đẩy. Mô hình này đang trở nên phổ biến trong các ứng dụng web hiện đại, cung cấp thêm tính linh hoạt.

- Vì vậy, cách đầu tiên để phân loại một ứng dụng máy chủ là theo chức năng (hoặc các chức năng) mà họ thực hiện hoặc một `Service` (hoặc các `Service`) mà họ cung cấp cho khách hàng của họ.

- Một thứ nguyên phân loại rõ ràng khác là giao thức lớp truyền tải được máy chủ sử dụng để giao tiếp với các máy khách.

- Giao thức TCP ngày nay rất phổ biến và nhiều ứng dụng máy chủ có mục đích chung sử dụng nó để giao tiếp. Các máy chủ khác, cụ thể hơn có thể sử dụng giao thức UDP. Các ứng dụng máy chủ kết hợp cung cấp `Service` của họ thông qua cả giao thức TCP và UDP cùng lúc thuộc loại thứ ba và được gọi là máy chủ đa giao thức. Trong chương này, chúng ta sẽ xem xét một số loại máy chủ TCP.

- Một đặc điểm nữa của máy chủ là cách thức mà nó phục vụ các máy khách. Một máy chủ lặp lại phục vụ các máy khách theo kiểu từng cái một, có nghĩa là nó không bắt đầu phục vụ máy khách tiếp theo trước khi hoàn thành việc phục vụ máy khách hiện đang phục vụ. Một máy chủ song song có thể phục vụ song song nhiều máy khách. Trên máy tính một bộ xử lý, một máy chủ song song đan xen các giai đoạn giao tiếp khác nhau với một số máy khách đang chạy chúng trên một bộ xử lý duy nhất. Ví dụ: đã kết nối với một máy khách và trong khi chờ thông báo yêu cầu từ nó, máy chủ có thể chuyển sang kết nối máy khách thứ hai hoặc đọc yêu cầu từ máy khách thứ ba; sau đó, nó có thể chuyển trở lại ứng dụng khách đầu tiên để tiếp tục phục vụ nó. Song song như vậy được gọi là song song giả, vì một bộ xử lý chỉ đơn thuần là chuyển đổi giữa một số máy khách, nhưng không phục vụ chúng thực sự đồng thời, điều này là không thể với một bộ xử lý duy nhất.

- Trên máy tính đa xử lý, khả năng song song thực sự có thể xảy ra, khi một máy chủ phục vụ nhiều hơn một máy khách cùng lúc sử dụng các luồng phần cứng khác nhau cho mỗi máy khách.

- Máy chủ lặp lại tương đối đơn giản để triển khai và có thể được sử dụng khi tốc độ yêu cầu đủ thấp để máy chủ có thời gian xử lý xong một yêu cầu trước khi yêu cầu tiếp theo đến. Rõ ràng là các máy chủ **iterative** không thể mở rộng; thêm nhiều bộ xử lý vào máy tính đang chạy một máy chủ như vậy sẽ không làm tăng thông lượng của máy chủ. Mặt khác, các máy chủ song song có thể xử lý tỷ lệ yêu cầu cao hơn; nếu được triển khai đúng cách, chúng có thể mở rộng. Một máy chủ thực sự song song chạy trên một máy tính đa xử lý có thể xử lý tỷ lệ yêu cầu cao hơn so với cùng một máy chủ chạy trên một máy tính xử lý đơn lẻ.

- Một cách khác để phân loại các ứng dụng máy chủ, theo quan điểm của người triển khai, là theo việc máy chủ là đồng bộ hay không đồng bộ. Máy chủ đồng bộ sử dụng lệnh gọi API socket đồng bộ chặn luồng thực thi cho đến khi hoàn thành hoạt động được yêu cầu, nếu không sẽ xảy ra lỗi. Do đó, một máy chủ TCP đồng bộ điển hình sẽ sử dụng các phương thức như `asio::ip::tcp::acceptor::accept()` để accept yêu cầu kết nối máy khách, `asio::ip::tcp::socket::read_some()` để nhận thông báo yêu cầu từ máy khách, và sau đó `asio::ip::tcp::socket::write_some()` để gửi lại thông báo phản hồi cho máy khách. Cả ba phương pháp đều đang chặn. Chúng chặn luồng thực thi cho đến khi hoàn thành hoạt động được yêu cầu hoặc xảy ra lỗi khiến máy chủ sử dụng các hoạt động này đồng bộ.

- Ứng dụng máy chủ không đồng bộ, trái ngược với ứng dụng đồng bộ, sử dụng lệnh gọi API **socket** không đồng bộ. Ví dụ: máy chủ TCP không đồng bộ có thể sử dụng phương thức `asio::ip::tcp::acceptor::async_accept()` để accept không đồng bộ yêu cầu kết nối máy khách, `asio::ip::tcp::socket::async_read_some()` phương thức hoặc hàm miễn phí `asio::async_read()` để nhận không đồng bộ thông báo yêu cầu từ máy khách và sau đó là phương thức `asio::ip::tcp::socket::async_write_some()` hoặc hàm miễn phí `asio::async_write()` để gửi một thông điệp phản hồi trở lại máy khách một cách không đồng bộ.

- Do cấu trúc của ứng dụng máy chủ đồng bộ khác biệt đáng kể so với cấu trúc của ứng dụng không đồng bộ, nên quyết định áp dụng phương pháp tiếp cận nào cần được thực hiện sớm ở giai đoạn thiết kế ứng dụng máy chủ và quyết định này phải dựa trên việc phân tích cẩn thận các yêu cầu của ứng dụng . Bên cạnh đó, các con đường phát triển ứng dụng có thể có và các yêu cầu mới có thể xuất hiện trong tương lai cần được xem xét và tính đến. Thông thường, mỗi cách tiếp cận đều có ưu điểm và nhược điểm. Khi một cách tiếp cận đồng bộ mang lại kết quả tốt hơn trong một tình huống, nó có thể hoàn toàn không được accept trong một tình huống khác; trong trường hợp này, cách tiếp cận không đồng bộ có thể là lựa chọn phù hợp. Hãy so sánh hai cách tiếp cận để hiểu rõ hơn về điểm mạnh và điểm yếu của mỗi cách tiếp cận.

- Ưu điểm chính của cách tiếp cận đồng bộ so với cách tiếp cận không đồng bộ là tính đơn giản của nó. Máy chủ đồng bộ dễ triển khai, gỡ lỗi và hỗ trợ hơn đáng kể so với máy chủ không đồng bộ ngang bằng về mặt chức năng. Máy chủ không đồng bộ phức tạp hơn do thực tế là các hoạt động không đồng bộ được chúng sử dụng hoàn thành ở những vị trí khác trong mã so với chúng được bắt đầu. Thông thường, điều này yêu cầu phân bổ cấu trúc dữ liệu bổ sung trong bộ nhớ trống để giữ ngữ cảnh của yêu cầu, thực hiện các chức năng gọi lại, đồng bộ hóa luồng và các tính năng bổ sung khác có thể làm cho cấu trúc ứng dụng khá phức tạp và dễ xảy ra lỗi. Hầu hết các tính năng bổ sung này không được yêu cầu trong các máy chủ đồng bộ. Bên cạnh đó, cách tiếp cận không đồng bộ mang lại chi phí tính toán và bộ nhớ bổ sung, điều này có thể làm cho nó kém hiệu quả hơn so với cách tiếp cận đồng bộ trong một số trường hợp.

- Tuy nhiên, cách tiếp cận đồng bộ có một số hạn chế về chức năng, điều này thường khiến nó không được accept. Những hạn chế này bao gồm việc không thể hủy một hoạt động đồng bộ sau khi nó đã bắt đầu hoặc ấn định thời gian chờ để nó bị gián đoạn nếu nó chạy quá lâu. Trái ngược với các hoạt động đồng bộ, các hoạt động không đồng bộ có thể bị hủy bất kỳ lúc nào sau khi hoạt động đã được bắt đầu.

- Thực tế là các hoạt động đồng bộ không thể bị hủy bỏ hạn chế đáng kể khu vực ứng dụng của các máy chủ đồng bộ. Các máy chủ công khai sử dụng các hoạt động đồng bộ rất dễ bị thủ phạm tấn công. Nếu một máy chủ như vậy là một luồng, một máy khách độc hại đủ để chặn máy chủ, không cho phép các máy khách khác giao tiếp với nó. Máy khách độc hại được thủ phạm sử dụng kết nối với máy chủ và không gửi bất kỳ dữ liệu nào đến máy chủ, trong khi máy khách bị chặn ở một trong các chức năng hoặc phương pháp đọc đồng bộ, không cho phép máy chủ phục vụ các máy khách khác.

- Các máy chủ như vậy thường sẽ được sử dụng trong môi trường an toàn và được bảo vệ trong mạng riêng hoặc như một phần nội bộ của ứng dụng chạy trên một máy tính sử dụng máy chủ như vậy để giao tiếp giữa các quá trình. Tất nhiên, một lĩnh vực ứng dụng có thể có khác của các máy chủ đồng bộ là việc triển khai các nguyên mẫu thử nghiệm.

- Bên cạnh sự khác biệt về độ phức tạp cấu trúc và chức năng được mô tả ở trên, hai cách tiếp cận còn khác nhau về hiệu quả và khả năng mở rộng khi phục vụ số lượng lớn khách hàng gửi yêu cầu với tỷ lệ cao. Máy chủ sử dụng hoạt động không đồng bộ hiệu quả hơn và có khả năng mở rộng hơn so với máy chủ đồng bộ, đặc biệt là khi chúng chạy trên máy tính đa xử lý có hệ điều hành hỗ trợ **I/O** mạng không đồng bộ.

### The sample protocol

- Trong chương này, chúng ta sẽ xem xét ba công thức mô tả cách triển khai máy chủ TCP lặp đồng bộ, máy chủ TCP song song đồng bộ và máy chủ TCP không đồng bộ. Trong tất cả các công thức, người ta giả định rằng máy chủ giao tiếp với máy khách bằng giao thức lớp ứng dụng được cố ý hóa (vì mục đích rõ ràng) sau đây.

- Một ứng dụng máy chủ accept các thông báo yêu cầu được biểu diễn dưới dạng chuỗi ASCII chứa một chuỗi ký hiệu kết thúc bằng ký hiệu ASCII dòng mới. Tất cả các ký hiệu đứng sau biểu tượng dòng mới đều bị máy chủ bỏ qua.

- Sau khi nhận được một yêu cầu, máy chủ thực hiện một số hoạt động giả và trả lời bằng một thông báo không đổi như sau:

```cpp
Response\n
```

- Một giao thức tầm thường như vậy cho phép chúng tôi tập trung vào việc triển khai máy chủ chứ không phải `Service` do nó cung cấp.

---

## Implementing a synchronous iterative TCP server

- Máy chủ TCP lặp đồng bộ là một phần của ứng dụng phân tán đáp ứng các tiêu chí sau:

    - Hoạt động như một máy chủ trong mô hình giao tiếp máy khách-máy chủ

    - Giao tiếp với các ứng dụng khách qua giao thức TCP

    - Sử dụng **I/O** và điều khiển các hoạt động chặn luồng thực thi cho đến khi hoạt động tương ứng hoàn thành hoặc lỗi xảy ra

    - Xử lý khách hàng theo kiểu nối tiếp, từng người một


- Máy chủ TCP **iterative** đồng bộ điển hình hoạt động theo thuật toán sau:

    - Phân bổ một **acceptor socket** và liên kết nó với một cổng TCP cụ thể.

    - Chạy một vòng cho đến khi máy chủ bị dừng:

        - Chờ yêu cầu kết nối từ máy khách.

        - accept yêu cầu kết nối của khách hàng khi có người đến.

        - Chờ thông báo yêu cầu từ máy khách.

        - Đọc thông báo yêu cầu.

        - Xử lý yêu cầu.

        - Gửi tin nhắn phản hồi đến máy khách.

        - Đóng kết nối với máy khách và phân bổ **socket**.

[**CODE**](asio-example/chapter-4/SyncIterative.cpp) - Công thức này trình bày cách triển khai ứng dụng máy chủ TCP **iterative** đồng bộ với `Boost.Asio`.

- Ứng dụng máy chủ mẫu bao gồm bốn thành phần — các lớp `Server`, `Acceptor`, và `Service` và hàm điểm nhập ứng dụng `main()`. Chúng ta hãy xem xét cách hoạt động của từng thành phần này.

### The Service class

- Lớp `Service` là thành phần chức năng chính trong toàn bộ ứng dụng. Trong khi các thành phần khác là cơ sở hạ tầng theo mục đích của chúng, lớp này thực hiện chức năng (hoặc `Service`) thực tế do máy chủ cung cấp cho các máy khách.

- Lớp này đơn giản và bao gồm một phương thức `HandleClient()` duy nhất. Phương thức này accept một đối tượng đại diện cho một **socket** được kết nối với máy khách làm đối số đầu vào của nó và xử lý máy khách cụ thể đó.

- Trong mẫu của chúng tôi, việc xử lý như vậy là không đáng kể. Đầu tiên, thông báo yêu cầu được đọc đồng bộ từ socket cho đến khi gặp biểu tượng ASCII dòng mới `\n`. Sau đó, yêu cầu được xử lý. Trong trường hợp của chúng tôi, chúng tôi mô phỏng xử lý bằng cách chạy một vòng lặp giả thực hiện một triệu hoạt động gia tăng và sau đó đặt luồng ở trạng thái ngủ trong nửa giây. Sau đó, thông báo phản hồi được chuẩn bị và gửi lại đồng bộ cho máy khách.

- Các ngoại lệ có thể được ném bởi các hàm và phương thức **I/O** Boost.Asio được bắt và xử lý trong phương thức `HandleClient()` và không được truyền tới trình gọi phương thức để nếu việc xử lý một máy khách không thành công, máy chủ sẽ tiếp tục hoạt động.

- Tùy thuộc vào nhu cầu của một ứng dụng cụ thể, lớp `Service` có thể được mở rộng và bổ sung thêm chức năng để cung cấp `Service` cần thiết.

### The `Acceptor` class

- Lớp `Acceptor` là một phần của cơ sở hạ tầng ứng dụng máy chủ. Khi được xây dựng, nó khởi tạo đối tượng socket của bộ accept `m_acceptor` và gọi phương thức `listen()` của nó để bắt đầu lắng nghe các yêu cầu kết nối từ máy khách.

- Lớp này hiển thị một phương thức công khai duy nhất có tên là `Accept()`. Phương thức này khi được gọi sẽ khởi tạo một đối tượng của lớp `asio::ip::tcp::socket` có tên là sock, đại diện cho một socket đang hoạt động và cố gắng accept một yêu cầu kết nối. Nếu có sẵn các yêu cầu kết nối đang chờ xử lý, yêu cầu kết nối sẽ được xử lý và sock **active socket** được kết nối với máy khách mới. Nếu không, phương thức này sẽ chặn cho đến khi có yêu cầu kết nối mới.

- Sau đó, một thể hiện của đối tượng Service được tạo và phương thức `HandleClient()` của nó được gọi. Đối tượng sock được kết nối với máy khách được chuyển đến phương thức này. Phương thức `HandleClient()` chặn cho đến khi giao tiếp với máy khách và xử lý yêu cầu hoàn tất, hoặc lỗi xảy ra. Khi phương thức `HandleClient()` trả về, phương thức `Accept()` của lớp `Acceptor` cũng trả về. Bây giờ, bộ accept đã sẵn sàng accept yêu cầu kết nối tiếp theo.

- Một lần thực thi phương thức `Accept()` của lớp thực hiện toàn bộ chu trình xử lý của một máy khách.

### The `Server` class

- Lớp `Server`, như tên gọi của nó, đại diện cho một máy chủ có thể được điều khiển thông qua các phương thức giao diện của lớp là `Start()` và `Stop()`.

- Phương thức `Start()` bắt đầu khởi động máy chủ. Nó sinh ra một luồng mới, bắt đầu thực thi từ phương thức riêng `Run()` của lớp Máy chủ và trả về. Phương thức `Run()` accept một đối số duy nhất có tên là port_num chỉ định số lượng cổng giao thức mà **acceptor socket** sẽ lắng nghe các yêu cầu kết nối đến. Khi được gọi, phương thức trước tiên khởi tạo một đối tượng của lớp `Acceptor` và sau đó bắt đầu một vòng lặp trong đó phương thức `Accept()` của đối tượng `Acceptor` được gọi. Vòng lặp kết thúc khi giá trị của biến **atomic** `m_stop` trở thành `true`, điều này xảy ra khi phương thức `Stop()` được gọi trên phiên bản tương ứng của lớp `Server`.

- Phương thức `Stop()` dừng đồng bộ máy chủ. Nó không quay trở lại cho đến khi vòng lặp bắt đầu trong phương thức `Run()` bị gián đoạn và luồng sinh ra bởi phương thức `Start()` kết thúc quá trình thực thi của nó. Để ngắt vòng lặp, giá trị của biến **atomic** `m_stop` được đặt thành `true`. Sau đó, phương thức `Stop()` gọi phương thức `join()` trên đối tượng m_thread đại diện cho luồng đang chạy vòng lặp trong phương thức `Run()` để đợi cho đến khi nó thoát khỏi vòng lặp và kết thúc quá trình thực thi.

- Việc triển khai được trình bày có một nhược điểm đáng kể bao gồm thực tế là máy chủ có thể không được dừng ngay lập tức. Hơn thế nữa, có khả năng máy chủ sẽ không bị dừng lại và phương thức `Stop()` sẽ chặn người gọi của nó mãi mãi. Nguyên nhân gốc rễ của vấn đề là do máy chủ có sự phụ thuộc cứng vào hành vi của các máy khách. Nếu phương thức `Stop()` được gọi và giá trị của biến **atomic** `m_stop` được đặt thành `true` trước điều kiện kết thúc vòng lặp trong `Run()` được kiểm tra, máy chủ bị dừng gần như ngay lập tức và không có sự cố nào xuất hiện. Tuy nhiên, nếu phương thức `Stop()` được gọi trong khi luồng của máy chủ bị chặn trong phương thức `acc.Accept()` đang chờ yêu cầu kết nối tiếp theo từ máy khách hoặc trong một trong các hoạt động **I/O** đồng bộ bên trong lớp **Service** đang chờ thông báo yêu cầu từ máy khách được kết nối hoặc để máy khách nhận thông báo phản hồi, máy chủ không thể dừng cho đến khi hoàn thành các hoạt động chặn này. Do đó, ví dụ: nếu hiện tại, khi phương thức `Stop()` được gọi, không có yêu cầu kết nối nào đang chờ xử lý, máy chủ sẽ không bị dừng cho đến khi một máy khách mới kết nối và được xử lý, điều này nói chung có thể không bao giờ xảy ra và sẽ dẫn đến máy chủ bị chặn mãi mãi.

- Sau đó, trong phần này, chúng tôi sẽ xem xét các cách có thể để khắc phục nhược điểm này.

### The `main()` entry point function

- Chức năng này thể hiện việc sử dụng máy chủ. Nó tạo một thể hiện của Serverclass có tên srv và gọi phương thức `Start()` của nó để khởi động máy chủ. Vì máy chủ được biểu diễn như một đối tượng đang hoạt động chạy trong luồng điều khiển của chính nó, phương thức `Start()` trả về ngay lập tức và phương thức chạy luồng `main()` tiếp tục thực thi. Để máy chủ chạy trong một khoảng thời gian, luồng chính được chuyển sang trạng thái ngủ trong 60 giây. Sau khi luồng chính thức dậy, nó gọi phương thức `Stop()` trên đối tượng srv để dừng máy chủ. Khi phương thức `Stop()` trả về, hàm `main()` cũng trả về và ứng dụng mẫu của chúng tôi sẽ thoát.

- Tất nhiên, trong ứng dụng thực, máy chủ sẽ bị dừng lại như một phản ứng với đầu vào của người dùng hoặc bất kỳ sự kiện liên quan nào khác, chứ không phải sau 60 giây giả, sau khi máy chủ hết thời gian khởi động.

### Eliminating the drawbacks

- Như nó đã được đề cập, việc triển khai đã trình bày có hai nhược điểm hạn chế đáng kể khả năng áp dụng của nó. Vấn đề đầu tiên là không thể dừng máy chủ nếu phương thức `Stop()` được gọi trong khi luồng máy chủ bị chặn khi chờ yêu cầu kết nối đến, không có yêu cầu kết nối nào đến. Vấn đề thứ hai là máy chủ có thể dễ dàng bị treo bởi một máy khách độc hại (hoặc lỗi), khiến nó không khả dụng với các máy khách khác. Để treo máy chủ, ứng dụng khách có thể chỉ cần kết nối với máy chủ và không bao giờ gửi bất kỳ yêu cầu nào đến nó, điều này sẽ khiến ứng dụng máy chủ bị treo trong thao tác chặn đầu vào mãi mãi.

- Nguyên nhân gốc rễ của cả hai vấn đề là do việc sử dụng các hoạt động chặn trong máy chủ (điều này là tự nhiên đối với các máy chủ đồng bộ). Một giải pháp hợp lý và đơn giản cho cả hai vấn đề này là chỉ định thời gian chờ cho các hoạt động chặn, điều này sẽ đảm bảo rằng máy chủ sẽ bỏ chặn theo định kỳ để kiểm tra xem lệnh dừng đã được đưa ra hay chưa và cũng để buộc loại bỏ các ứng dụng không gửi yêu cầu cho một khoảng thời gian dài. Tuy nhiên, Boost.Asio không cung cấp cách hủy các hoạt động đồng bộ hoặc ấn định thời gian chờ cho chúng. Do đó, chúng tôi nên cố gắng tìm các cách khác để làm cho máy chủ đồng bộ của chúng tôi phản hồi và ổn định hơn.

- Hãy xem xét các cách để giải quyết từng nhược điểm.

### Stopping a server in reasonable amount of time

- Vì cách hợp pháp duy nhất để bỏ chặn phương thức đồng bộ `accept()` của **acceptor socket** khi không có yêu cầu kết nối nào đang chờ xử lý là gửi một yêu cầu kết nối giả đến cổng mà bộ accept đang lắng nghe, chúng ta có thể thực hiện thủ thuật sau để giải quyết vấn đề của chúng ta.

- Trong phương thức `Stop()` của lớp Máy chủ, sau khi đặt giá trị của biến **atomic** `m_stop` thành true, chúng ta có thể tạo một **active socket** giả, kết nối nó với cùng một máy chủ này và gửi một số yêu cầu giả. Điều này sẽ đảm bảo rằng luồng máy chủ sẽ rời khỏi phương thức `accept()` của **acceptor socket** và cuối cùng sẽ kiểm tra giá trị của biến **atomic** `m_stop` để tìm ra rằng giá trị của nó bằng true, điều này sẽ dẫn đến việc kết thúc vòng lặp và hoàn thành của phương thức `Acceptor::Accept()`.

- Trong phương pháp được mô tả, giả định rằng máy chủ tự dừng lại bằng cách gửi một thông báo đến chính nó (thực ra một thông báo được gửi từ một luồng **I/O** tới luồng worker). Một cách tiếp cận khác là có một ứng dụng khách đặc biệt (ứng dụng riêng biệt) sẽ kết nối và gửi thông báo **Service** đặc biệt (ví dụ: dừng `\n`) đến máy chủ, thông báo này sẽ được máy chủ hiểu là tín hiệu dừng. Trong trường hợp này, máy chủ sẽ được điều khiển bên ngoài (từ một ứng dụng khác) và lớp Máy chủ sẽ không cần phải có phương thức `Stop()`.

### Dealing with the server's vulnerability

- Thật không may, bản chất của việc chặn hoạt động **I/O** mà không có thời gian chờ được chỉ định cho nó là nó có thể được sử dụng để dễ dàng treo máy chủ lặp lại sử dụng các hoạt động đó và khiến máy khách khác không thể truy cập được.

- Rõ ràng, để bảo vệ máy chủ khỏi lỗ hổng này, chúng ta cần thiết kế lại nó để nó không bao giờ bị chặn bởi các hoạt động **I/O**. Một cách để đạt được điều này là sử dụng các **socket** không chặn (sẽ biến máy chủ của chúng tôi thành phản ứng) hoặc sử dụng các hoạt động **I/O** không đồng bộ. Cả hai tùy chọn đều có nghĩa là máy chủ của chúng tôi ngừng đồng bộ. Chúng tôi sẽ xem xét một số giải pháp này trong các công thức nấu ăn khác của chương này.

### Analyzing the results

- Các lỗ hổng vốn có trong các máy chủ lặp lại đồng bộ được triển khai với Boost.Asio được mô tả ở trên không cho phép sử dụng chúng trong các mạng công cộng, nơi có nguy cơ bị thủ phạm sử dụng sai máy chủ. Thông thường, các máy chủ đồng bộ sẽ được sử dụng trong môi trường đóng và được bảo vệ, nơi các máy khách được thiết kế cẩn thận để chúng không bị treo máy chủ.

- Một hạn chế khác của máy chủ đồng bộ lặp là chúng không thể mở rộng và không thể tận dụng phần cứng đa xử lý. Tuy nhiên, ưu điểm của chúng - sự đơn giản là lý do tại sao loại máy chủ này là một lựa chọn tốt trong nhiều trường hợp.

---

## Implementing a synchronous parallel TCP server

- Máy chủ TCP song song đồng bộ là một phần của ứng dụng phân tán đáp ứng các tiêu chí sau:

    - Hoạt động như một máy chủ trong mô hình giao tiếp máy khách-máy chủ

    - Giao tiếp với các ứng dụng khách qua giao thức TCP

    - Sử dụng **I/O** và điều khiển các hoạt động chặn luồng thực thi cho đến khi hoạt động tương ứng hoàn thành hoặc lỗi xảy ra

    - Có thể xử lý nhiều hơn một khách hàng đồng thời

- Một máy chủ TCP song song đồng bộ điển hình hoạt động theo thuật toán sau:

    - Phân bổ một **socket** bộ nhận và liên kết nó với một cổng TCP cụ thể.

    - Chạy một vòng cho đến khi máy chủ bị dừng:

        - Chờ yêu cầu kết nối đến từ máy khách

        - accept yêu cầu kết nối của khách hàng

        - Tạo ra một chuỗi điều khiển và trong ngữ cảnh của chuỗi này:

            - Chờ thông báo yêu cầu từ khách hàng

            - Đọc thông báo yêu cầu

            - Xử lý yêu cầu

            - Gửi tin nhắn phản hồi cho khách hàng

            - Đóng kết nối với máy khách và phân bổ **socket**

[**CODE**](asio-example/chapter-4/SyncParallel.cpp) - This recipe demonstrates how to implement a synchronous parallel TCP server application with Boost.Asio.

- The sample server application consists of four components—the `Server`, `Acceptor`, and `Service` classes and the application entry point function `main()`. Let's consider how each of these components work.

- Ứng dụng máy chủ mẫu bao gồm bốn thành phần — các lớp `Server`, `Acceptor`, và `Service` và hàm điểm nhập ứng dụng `main()`. Chúng ta hãy xem xét cách hoạt động của từng thành phần này.

### The `Service` class

- Lớp **Service** là thành phần chức năng chính trong toàn bộ ứng dụng. Trong khi các thành phần khác cấu thành cơ sở hạ tầng của máy chủ, lớp này thực hiện chức năng (hoặc **Service**) thực tế do máy chủ cung cấp cho các máy khách.

- Lớp này có một phương thức duy nhất trong giao diện của nó được gọi là `StartHandlingClient()`. Phương thức này accept một con trỏ đến một đối tượng đại diện cho một **socket** TCP được kết nối với máy khách làm đối số đầu vào của nó và bắt đầu xử lý máy khách cụ thể đó.

- Phương thức này sinh ra một luồng điều khiển, bắt đầu thực thi nó từ phương thức riêng `HandleClient()` của lớp, nơi xử lý đồng bộ thực sự được thực hiện. Sau khi tạo ra luồng, phương thức `StartHandlingClient()` "để nó hoạt động" bằng cách tách luồng khỏi đối tượng `std::thread` đại diện cho nó. Sau đó, phương thức `StartHandlingClient()` trả về.

- Phương thức `private HandleClient()`, như tên gọi của nó, xử lý client. Trong mẫu của chúng tôi, việc xử lý như vậy là không đáng kể. Đầu tiên, thông báo yêu cầu được đọc đồng bộ từ socket cho đến khi gặp biểu tượng ASCII dòng mới `\n`. Sau đó, yêu cầu được xử lý. Trong trường hợp của chúng tôi, chúng tôi mô phỏng xử lý bằng cách chạy một vòng lặp giả thực hiện một triệu hoạt động gia tăng và sau đó đặt luồng ở trạng thái ngủ trong nửa giây. Sau đó, thông báo phản hồi được chuẩn bị và gửi lại cho khách hàng.

- Khi thông báo phản hồi được gửi đi, đối tượng của lớp **Service** được liên kết với phương thức `HandleClient()`, hiện đang chạy, sẽ bị xóa bởi toán tử xóa. Tất nhiên, thiết kế của lớp giả định rằng các thể hiện của nó sẽ được cấp phát trong bộ nhớ trống bởi một toán tử mới chứ không phải trên ngăn xếp.

- Tùy thuộc vào nhu cầu của một ứng dụng cụ thể, lớp **Service** có thể được mở rộng và làm phong phú thêm chức năng để cung cấp **Service** cần thiết.

### The `Acceptor` class

- Lớp `Acceptor` là một phần của cơ sở hạ tầng ứng dụng máy chủ. Khi được xây dựng, nó khởi tạo đối tượng socket của bộ accept `m_acceptor` và gọi phương thức `listen()` của nó để bắt đầu lắng nghe các yêu cầu kết nối từ máy khách.

- Lớp này hiển thị một phương thức công khai `Accept()` duy nhất. Phương thức này khi được gọi sẽ khởi tạo một đối tượng của lớp `asio::ip::tcp::socket` có tên là sock, đại diện cho một socket đang hoạt động và cố gắng accept một yêu cầu kết nối. Nếu có sẵn các yêu cầu kết nối đang chờ xử lý, yêu cầu kết nối sẽ được xử lý và sock **active socket** được kết nối với máy khách mới. Nếu không, phương thức này sẽ chặn cho đến khi có yêu cầu kết nối mới.

- Sau đó, một thể hiện của đối tượng Service được cấp phát trong bộ nhớ trống và phương thức `StartHandlingClient()` của nó được gọi. Đối tượng sock được truyền cho phương thức này như một đối số đầu vào. Phương thức `StartHandlingClient()` sinh ra một luồng trong ngữ cảnh mà ứng dụng khách sẽ được xử lý và trả về ngay lập tức. Khi phương thức `StartHandlingClient()` trả về, phương thức `Accept()` của bộ accept

- Lớp cũng trả về. Bây giờ, bộ accept đã sẵn sàng để accept yêu cầu kết nối tiếp theo. Lưu ý rằng bộ accept không có quyền sở hữu đối tượng của lớp **Service**. Thay vào đó, đối tượng của lớp **Service** sẽ tự hủy khi nó hoàn thành công việc của mình.

### The `Server` class

- Lớp `Server`, như tên gọi của nó, đại diện cho một máy chủ có thể được điều khiển thông qua các phương thức `Start()` và `Stop()` trong giao diện của lớp.

- Phương thức `Start()` bắt đầu khởi động máy chủ. Nó sinh ra một luồng mới bắt đầu thực thi từ phương thức riêng `Run()` của lớp Máy chủ và trả về. Phương thức `Run()` accept một đối số duy nhất `port_num` chỉ định số cổng giao thức mà **acceptor socket** sẽ lắng nghe các yêu cầu kết nối đến. Khi được gọi, phương thức trước tiên khởi tạo một đối tượng của lớp `Acceptor` và sau đó bắt đầu một vòng lặp trong đó phương thức `Accept()` của đối tượng `Acceptor` được gọi. Vòng lặp kết thúc khi giá trị của biến **atomic** `m_stop` trở thành `true`, điều này xảy ra khi phương thức `Stop()` được gọi trên phiên bản tương ứng của lớp `Server`.

- Phương thức `Stop()` dừng đồng bộ máy chủ. Nó không quay trở lại cho đến khi một vòng lặp bắt đầu trong phương thức `Run()` bị gián đoạn và luồng được tạo bởi phương thức `Start()` kết thúc quá trình thực thi của nó. Để ngắt vòng lặp, giá trị của biến **atomic** `m_stop` được đặt thành `true`. Sau đó, phương thức `Stop()` gọi phương thức `join()` trên đối tượng `m_thread` đại diện cho luồng đang chạy vòng lặp trong phương thức `Run()` để đợi cho đến khi nó kết thúc quá trình thực thi.

- Việc triển khai được trình bày có một nhược điểm đáng kể bao gồm thực tế là máy chủ có thể không được dừng ngay lập tức. Hơn thế nữa, có khả năng máy chủ sẽ không bị dừng lại và phương thức `Stop()` sẽ chặn người gọi của nó mãi mãi. Nguyên nhân sâu xa của vấn đề là do máy chủ phụ thuộc nhiều vào hành vi của các máy khách.

- Nếu phương thức `Stop()` được gọi và đặt giá trị của biến **atomic** biến `m_stop` thành `true` ngay trước khi điều kiện kết thúc vòng lặp trong phương thức `Run()` được kiểm tra, máy chủ sẽ bị dừng gần như ngay lập tức và không có vấn đề gì xảy ra. Tuy nhiên, nếu phương thức `Stop()` được gọi trong khi luồng của máy chủ bị chặn trong phương thức `acc.Accept()` đang chờ yêu cầu kết nối tiếp theo từ máy khách — hoặc trong một trong các hoạt động **I/O** đồng bộ bên trong lớp **Service** đang chờ thông báo yêu cầu từ máy khách được kết nối hoặc để máy khách nhận thông báo phản hồi — máy chủ không thể dừng cho đến khi các hoạt động chặn này hoàn tất. Do đó, ví dụ: nếu tại thời điểm khi phương thức `Stop()` được gọi, không có yêu cầu kết nối nào đang chờ xử lý, máy chủ sẽ không bị dừng cho đến khi một máy khách mới kết nối và được xử lý, điều này nói chung có thể không bao giờ xảy ra và có thể dẫn đến đến máy chủ bị chặn vĩnh viễn.

- Sau đó, trong phần này, chúng tôi sẽ xem xét các cách khả thi để khắc phục nhược điểm này.

### The `main()` entry point function

- Chức năng này thể hiện việc sử dụng máy chủ. Nó tạo một thể hiện của lớp `Server` có tên srv và gọi phương thức của nó là `Start()` để khởi động máy chủ. Vì máy chủ được biểu diễn như một đối tượng đang hoạt động chạy trong luồng điều khiển của chính nó, phương thức `Start()` trả về ngay lập tức và luồng chạy phương thức `main()` tiếp tục thực thi. Để cho phép máy chủ chạy trong một thời gian, luồng chính được chuyển sang trạng thái ngủ trong 60 giây. Sau khi luồng chính thức dậy, nó gọi phương thức `Stop()` trên đối tượng srv để dừng máy chủ. Khi phương thức `Stop()` trả về, hàm `main()` cũng trả về và ứng dụng mẫu của chúng tôi sẽ thoát.

- Tất nhiên, trong ứng dụng thực, máy chủ sẽ bị dừng lại như một phản ứng với đầu vào của người dùng hoặc bất kỳ sự kiện liên quan nào khác, chứ không phải sau 60 giây giả sau khi máy chủ khởi động hết.

### Eliminating the drawbacks

- Những hạn chế vốn có trong ứng dụng máy chủ song song đồng bộ được triển khai với thư viện Boost.Asio tương tự như những hạn chế của ứng dụng máy chủ lặp đồng bộ được xem xét trong công thức trước. Vui lòng tham khảo công thức triển khai máy chủ TCP lặp đồng bộ để thảo luận về các nhược điểm và cách loại bỏ chúng.

---

## Implementing an asynchronous TCP server

- Máy chủ TCP không đồng bộ là một phần của ứng dụng phân tán đáp ứng các tiêu chí sau:

    - Hoạt động như một máy chủ trong mô hình giao tiếp máy khách-máy chủ

    - Giao tiếp với các ứng dụng khách qua giao thức TCP

    - Sử dụng **I/O** không đồng bộ và các hoạt động điều khiển

    - Có thể xử lý nhiều khách hàng đồng thời

- Máy chủ TCP không đồng bộ điển hình hoạt động theo thuật toán sau:

    - Phân bổ một **acceptor socket** và liên kết nó với một cổng TCP cụ thể.

    - Bắt đầu hoạt động accept không đồng bộ.

    - Tạo ra một hoặc nhiều luồng điều khiển và thêm chúng vào nhóm các luồng chạy vòng lặp sự kiện Boost.Asio.

    - Khi hoạt động accept không đồng bộ hoàn tất, hãy khởi tạo một thao tác mới để accept yêu cầu kết nối tiếp theo.

    - Bắt đầu thao tác đọc không đồng bộ để đọc yêu cầu từ máy khách được kết nối.

    - Khi hoạt động đọc không đồng bộ hoàn thành, xử lý yêu cầu và chuẩn bị thông báo phản hồi.

    - Bắt đầu thao tác ghi không đồng bộ để gửi thông điệp phản hồi đến máy khách.

    - Khi hoạt động ghi không đồng bộ hoàn tất, đóng kết nối và phân bổ **socket**.

- Lưu ý rằng các bước bắt đầu từ bước thứ tư trong thuật toán trước đó có thể được thực hiện theo thứ tự tùy ý tùy thuộc vào thời gian tương đối của các hoạt động không đồng bộ cụ thể trong một ứng dụng cụ thể. Do mô hình không đồng bộ của máy chủ, thứ tự thực hiện tuần tự của các bước có thể không giữ ngay cả khi máy chủ đang chạy trên một máy tính bộ xử lý.

[**CODE**](asio-example/chapter-4/AsyncParallel.cpp) - This recipe demonstrates how to implement an asynchronous TCP server application with `Boost.Asio`.

- Ứng dụng máy chủ mẫu bao gồm bốn thành phần — các lớp `Service`, `Acceptor` và `Service` và một hàm điểm nhập ứng dụng `main()`. Chúng ta hãy xem xét cách hoạt động của từng thành phần này.

### The `Service` class

- Lớp **Service** là thành phần chức năng chính trong ứng dụng. Trong khi các thành phần khác cấu thành cơ sở hạ tầng của máy chủ, lớp này thực hiện chức năng (hoặc **Service**) thực tế do máy chủ cung cấp cho các máy khách.

- Một phiên bản của lớp này nhằm xử lý một máy khách được kết nối duy nhất bằng cách đọc
yêu cầu, xử lý nó, và sau đó gửi lại tin nhắn phản hồi.

- Phương thức khởi tạo của lớp accept một con trỏ dùng chung tới một đối tượng đại diện cho một socket được kết nối với một máy khách cụ thể như một đối số và lưu vào bộ nhớ cache con trỏ này. Ổ cắm này sẽ được sử dụng sau này để giao tiếp với ứng dụng khách.

- Giao diện chung của lớp Service bao gồm một phương thức duy nhất `StartHandling()`. Phương thức này bắt đầu xử lý máy khách bằng cách bắt đầu thao tác đọc không đồng bộ để đọc thông báo yêu cầu từ máy khách chỉ định phương thức `onRequestReceive()` như một cuộc gọi lại. Sau khi bắt đầu thao tác đọc không đồng bộ, phương thức `StartHandling()` sẽ trả về.

- Khi quá trình đọc yêu cầu hoàn tất hoặc xảy ra lỗi, phương thức gọi lại `onRequestReceive()` được gọi. Phương pháp này trước tiên kiểm tra xem việc đọc có thành công hay không bằng cách kiểm tra đối số ec có chứa mã trạng thái hoàn thành hoạt động. Trong trường hợp quá trình đọc kết thúc mà có lỗi, thông báo tương ứng được xuất ra luồng đầu ra tiêu chuẩn và sau đó phương thức `onFinish()` được gọi. Sau đó, phương thức `onRequestReceieved()` trả về, dẫn đến gián đoạn quá trình xử lý máy khách.

- Nếu thông báo yêu cầu đã được đọc thành công, phương thức `ProcessRequest()` được gọi để thực hiện các hoạt động được yêu cầu và chuẩn bị thông báo phản hồi. Khi phương thức `ProcessRequest()` hoàn thành và trả về chuỗi chứa thông báo phản hồi, thì thao tác ghi không đồng bộ được bắt đầu để gửi thông báo phản hồi này trở lại máy khách. Phương thức `onResponseSent()` được chỉ định như một cuộc gọi lại.

- Khi thao tác ghi hoàn tất (hoặc xảy ra lỗi), phương thức `onResponseSent()` được gọi. Phương pháp này đầu tiên kiểm tra xem hoạt động có thành công hay không. Nếu thao tác không thành công, thông báo tương ứng được xuất ra luồng đầu ra tiêu chuẩn. Tiếp theo, phương thức `onFinish()` được gọi để thực hiện dọn dẹp. Khi phương thức `onFinish()` trả về, toàn bộ chu trình xử lý máy khách được coi là đã hoàn thành.

- Phương thức `ProcessRequest()` là trung tâm của lớp vì nó thực thi **Service**. Trong ứng dụng máy chủ của chúng tôi, chúng tôi có một **Service** giả chạy một vòng lặp giả thực hiện một triệu hoạt động gia tăng và sau đó đặt luồng ở trạng thái ngủ trong 100 mili giây. Sau đó, thông báo phản hồi giả được tạo và trả lại cho người gọi.

- Tùy thuộc vào nhu cầu của một ứng dụng cụ thể, lớp **Service** và đặc biệt là phương thức `ProcessRequest()` của nó có thể được mở rộng và bổ sung thêm chức năng để cung cấp **Service** cần thiết.

- Lớp **Service** được thiết kế để các đối tượng của nó tự xóa khi công việc của chúng hoàn thành. Việc xóa được thực hiện trong phương thức `private onFinish()` của lớp, phương thức này được gọi vào cuối chu trình xử lý máy khách cho dù nó thành công hay sai:

```cpp
void `onFinish()`
{
    delete this;
}
```

### The `Acceptor` class

- Lớp `Acceptor` là một phần của cơ sở hạ tầng của ứng dụng máy chủ. Hàm tạo của nó accept một số cổng mà nó sẽ lắng nghe các yêu cầu kết nối đến làm đối số đầu vào của nó. Đối tượng của lớp này chứa một thể hiện của lớp `asio::ip::tcp::acceptor` làm thành viên của nó có tên là `m_acceptor`, được xây dựng trong phương thức khởi tạo của lớp `Acceptor`.

- Lớp `Acceptor` hiển thị hai phương thức công khai — `Start()` và `Stop()`. Phương thức `Start()` nhằm hướng dẫn một đối tượng của lớp `Acceptor` bắt đầu lắng nghe và accept các yêu cầu kết nối đến. Nó đặt socket của bộ accept `m_acceptor` vào chế độ lắng nghe và sau đó gọi phương thức riêng ``InitAccept()`` của lớp. Đến lượt mình, phương thức ``InitAccept()`` lại xây dựng một đối tượng **active socket** và bắt đầu hoạt động accept không đồng bộ, gọi phương thức `async_accept()` trên đối tượng **acceptor socket** và chuyển đối tượng đại diện cho một **active socket** cho nó như một đối số. Phương thức `onAccept()` của lớp `Acceptor` được chỉ định như một cuộc gọi lại.

- Khi yêu cầu kết nối được accept hoặc xảy ra lỗi, phương thức gọi lại `onAccept()` được gọi. Đầu tiên, phương pháp này kiểm tra xem có bất kỳ lỗi nào xảy ra trong khi hoạt động không đồng bộ được thực hiện hay không bằng cách kiểm tra giá trị của đối số đầu vào ec. Nếu thao tác hoàn tất thành công, một thể hiện của lớp Dịch vụ được tạo và phương thức `StartHandling()` của nó được gọi, phương thức này bắt đầu xử lý ứng dụng khách được kết nối. Ngược lại, trong trường hợp lỗi, thông báo tương ứng được xuất ra luồng đầu ra tiêu chuẩn.

- Tiếp theo, giá trị của biến **atomic** `m_isStopped` được kiểm tra xem lệnh dừng đã được đưa ra trên đối tượng `Acceptor` hay chưa. Nếu nó có (có nghĩa là phương thức `Stop()` đã được gọi trên đối tượng `Acceptor`), một hoạt động accept không đồng bộ mới sẽ không được bắt đầu và đối tượng bộ accept mức thấp bị đóng. Tại thời điểm này, Bộ `Acceptor` ngừng lắng nghe và accept các yêu cầu kết nối đến từ máy khách. Nếu không, phương thức 1 được gọi để bắt đầu hoạt động accept không đồng bộ mới để accept yêu cầu kết nối đến tiếp theo.

Như nó đã được đề cập, phương thức `Stop()` hướng dẫn đối tượng `Acceptor` không bắt đầu thao tác accept không đồng bộ tiếp theo khi thao tác hiện đang chạy hoàn tất. Tuy nhiên, thao tác accept hiện đang chạy không bị hủy bằng phương pháp này.

### The `Server` class

- Lớp `Acceptor` là một phần của cơ sở hạ tầng của ứng dụng máy chủ. Hàm tạo của nó chấp nhận một số cổng mà nó sẽ lắng nghe các yêu cầu kết nối đến làm đối số đầu vào của nó. Đối tượng của lớp này chứa một thể hiện của lớp `asio::ip::tcp::acceptor` làm thành viên của nó có tên là `m_acceptor`, được xây dựng trong phương thức khởi tạo của lớp `Acceptor`.

- Lớp `Acceptor` hiển thị hai phương thức công khai — `Start()` và `Stop()`. Phương thức `Start()` nhằm hướng dẫn một đối tượng của lớp Acceptor bắt đầu lắng nghe và chấp nhận các yêu cầu kết nối đến. Nó đặt socket của bộ `Acceptor` `m_acceptor` vào chế độ lắng nghe và sau đó gọi phương thức riêng `InitAccept()` của lớp. Đến lượt mình, phương thức `InitAccept()` lại xây dựng một đối tượng **active socket** và bắt đầu hoạt động `Acceptor` không đồng bộ, gọi phương thức `async_accept()` trên đối tượng ổ cắm chấp nhận và chuyển đối tượng đại diện cho một **active socket** cho nó như một đối số. Phương thức `onAccept()` của lớp `Acceptor` được chỉ định như một cuộc gọi lại.

- Khi yêu cầu kết nối được chấp nhận hoặc xảy ra lỗi, phương thức gọi lại `onAccept()` được gọi. Đầu tiên, phương pháp này kiểm tra xem có bất kỳ lỗi nào xảy ra trong khi hoạt động không đồng bộ được thực hiện hay không bằng cách kiểm tra giá trị của đối số đầu vào ec. Nếu thao tác hoàn tất thành công, một thể hiện của lớp Dịch vụ được tạo và phương thức `StartHandling()` của nó được gọi, phương thức này bắt đầu xử lý ứng dụng khách được kết nối. Ngược lại, trong trường hợp lỗi, thông báo tương ứng được xuất ra luồng đầu ra tiêu chuẩn.

- Tiếp theo, giá trị của biến **atomic** `m_isStopped` được kiểm tra xem lệnh dừng đã được đưa ra trên đối tượng `Acceptor` hay chưa. Nếu nó có (có nghĩa là phương thức `Stop()` đã được gọi trên đối tượng `Acceptor`), một hoạt động chấp nhận không đồng bộ mới sẽ không được bắt đầu và đối tượng bộ chấp nhận mức thấp bị đóng. Tại thời điểm này, Bộ chấp nhận ngừng lắng nghe và chấp nhận các yêu cầu kết nối đến từ máy khách. Nếu không, phương thức `InitAccept()` được gọi để bắt đầu hoạt động chấp nhận không đồng bộ mới để chấp nhận yêu cầu kết nối đến tiếp theo.

Như nó đã được đề cập, phương thức `Stop()` hướng dẫn đối tượng `Acceptor` không bắt đầu thao tác chấp nhận không đồng bộ tiếp theo khi thao tác hiện đang chạy hoàn tất. Tuy nhiên, thao tác chấp nhận hiện đang chạy không bị hủy bằng phương pháp này.

### The `main()` entry point function

- Chức năng này thể hiện việc sử dụng máy chủ. Đầu tiên, nó khởi tạo một đối tượng của lớp Server có tên srv. Bởi vì phương thức `Start()` của lớp Máy chủ yêu cầu một số luồng cấu thành một nhóm phải được chuyển đến nó, trước khi khởi động máy chủ, kích thước tối ưu của nhóm sẽ được tính toán. Công thức chung thường được sử dụng trong các ứng dụng song song để tìm số luồng tối ưu là số bộ xử lý mà máy tính đã nhân với 2. Chúng ta sử dụng phương thức tĩnh `std::thread::hardware_concurrency()` để lấy số bộ xử lý. Tuy nhiên, vì phương thức này có thể không thực hiện được công việc của nó trả về 0, chúng tôi quay trở lại giá trị mặc định được biểu thị bằng hằng số `DEFAULT_THREAD_POOL_SIZE`, bằng 2 trong trường hợp của chúng tôi.

- Khi kích thước nhóm luồng được tính toán, phương thức `Start()` được gọi để khởi động máy chủ. Phương thức `Start()` không chặn. Khi nó trả về, luồng chạy phương thức `main()` sẽ tiếp tục thực thi. Để cho phép máy chủ chạy trong một thời gian, luồng chính được chuyển sang trạng thái ngủ trong 60 giây. Khi luồng chính thức dậy, nó gọi phương thức `Stop()` trên đối tượng srv để dừng máy chủ. Khi phương thức `Stop()` trả về, hàm `main()` cũng trả về và ứng dụng của chúng ta sẽ thoát.

- Tất nhiên, trong ứng dụng thực, máy chủ sẽ bị dừng lại như một phản ứng đối với một số sự kiện liên quan chẳng hạn như thông tin người dùng nhập, thay vì khi một khoảng thời gian giả nào đó trôi qua.

---