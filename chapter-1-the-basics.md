# Chapter 1 - The Basics

## Introduction

- Mạng máy tính và các giao thức truyền thông làm tăng đáng kể khả năng của phần mềm hiện đại, cho phép các ứng dụng khác nhau hoặc các phần riêng biệt của cùng một ứng dụng giao tiếp với nhau để đạt được một mục tiêu chung. Một số ứng dụng có chức năng chính là giao tiếp, chẳng hạn như trình nhắn tin tức thời, máy chủ e-mail và ứng dụng khách, phần mềm tải xuống tệp, v.v. Những người khác có lớp giao tiếp mạng như một thành phần cơ bản, trên đó có chức năng chính được xây dựng. Một số ví dụ về các ứng dụng đó là trình duyệt web, hệ thống tệp mạng, hệ thống quản lý cơ sở dữ liệu phân tán, phần mềm phát trực tuyến đa phương tiện, trò chơi trực tuyến, trò chơi ngoại tuyến với nhiều người chơi qua hỗ trợ tùy chọn mạng và nhiều trò chơi khác. Bên cạnh đó, ngày nay hầu hết mọi ứng dụng ngoài chức năng chính đều cung cấp các chức năng phụ, liên quan đến giao tiếp mạng. Ví dụ nổi bật nhất của các chức năng này là đăng ký trực tuyến và cập nhật phần mềm tự động. Trong trường hợp thứ hai, gói cập nhật được tải xuống từ máy chủ từ xa của nhà phát triển ứng dụng và được cài đặt trên máy tính hoặc thiết bị di động của người dùng.

- Ứng dụng bao gồm hai hoặc nhiều phần, mỗi phần chạy trên một thiết bị tính toán riêng biệt và giao tiếp với các phần khác qua mạng máy tính được gọi là ứng dụng phân tán. Ví dụ, một máy chủ web và một trình duyệt web cùng nhau có thể được coi là một ứng dụng phân tán phức tạp. Trình duyệt chạy trên máy tính của người dùng giao tiếp với máy chủ web đang chạy trên một máy tính từ xa khác để đạt được mục tiêu chung - truyền và hiển thị trang web do người dùng yêu cầu.

- Các ứng dụng phân tán cung cấp những lợi ích đáng kể so với các ứng dụng truyền thống chạy trên một máy tính. Giá trị nhất trong số đó là:

    - Khả năng truyền dữ liệu giữa hai hoặc nhiều thiết bị tính toán từ xa. Đây là điều hoàn toàn hiển nhiên và là lợi ích quý giá nhất của phần mềm phân tán.
    - Khả năng kết nối các máy tính trong mạng và cài đặt phần mềm đặc biệt trên chúng, tạo ra các hệ thống máy tính mạnh mẽ có thể thực hiện các tác vụ không thể thực hiện trên một máy tính trong một khoảng thời gian thích hợp.
    - Khả năng lưu trữ và chia sẻ dữ liệu trong mạng một cách hiệu quả. Trong mạng máy tính, một thiết bị duy nhất có thể được sử dụng làm bộ lưu trữ dữ liệu để lưu trữ lượng lớn dữ liệu và các thiết bị khác có thể dễ dàng yêu cầu một số phần của dữ liệu đó khi cần thiết mà không cần phải giữ bản sao của tất cả dữ liệu trên mỗi thiết bị. Ví dụ, hãy xem xét các trung tâm dữ liệu lớn lưu trữ hàng trăm triệu trang web. Người dùng cuối có thể yêu cầu trang web mà họ cần bất cứ lúc nào bằng cách gửi yêu cầu đến máy chủ qua mạng (thường là Internet). Không cần phải giữ bản sao của trang web trên thiết bị của người dùng. Có một bộ lưu trữ dữ liệu duy nhất (một trang web) và hàng triệu người dùng có thể yêu cầu dữ liệu từ bộ lưu trữ đó nếu và khi thông tin này là cần thiết.

- Để hai ứng dụng chạy trên các thiết bị tính toán khác nhau có thể giao tiếp với nhau, chúng cần phải đồng ý về một giao thức truyền thông. Tất nhiên, nhà phát triển ứng dụng phân tán có thể tự do triển khai giao thức của riêng mình. Tuy nhiên, điều này hiếm khi xảy ra ít nhất vì hai lý do. Đầu tiên, việc phát triển một giao thức như vậy là một nhiệm vụ cực kỳ phức tạp và tốn thời gian. Thứ hai, các giao thức như vậy đã được xác định, chuẩn hóa và thậm chí được triển khai trong tất cả các hệ điều hành phổ biến bao gồm Windows, Mac OS X và phần lớn các bản phân phối của Linux.

- Các giao thức này được xác định bởi tiêu chuẩn TCP / IP. Đừng để bị lừa bởi tên của tiêu chuẩn; nó xác định không chỉ TCP và IP mà còn nhiều giao thức khác, bao gồm ngăn xếp giao thức TCP / IP với một hoặc nhiều giao thức trên mỗi cấp của ngăn xếp. Các nhà phát triển phần mềm phân tán thường xử lý các giao thức cấp độ truyền tải như TCP hoặc UDP. Các giao thức lớp dưới thường bị ẩn khỏi nhà phát triển và được xử lý bởi hệ điều hành và các thiết bị mạng.

- Giao thức TCP là một giao thức lớp truyền tải với các đặc điểm sau:

    - Đáng tin cậy, có nghĩa là giao thức này đảm bảo gửi tin nhắn theo đúng thứ tự hoặc thông báo rằng tin nhắn chưa được gửi. Giao thức bao gồm các cơ chế xử lý lỗi, giúp giải phóng nhà phát triển khỏi sự cần thiết phải triển khai chúng trong ứng dụng.

    - Nó giả định thiết lập kết nối logic. Trước khi một ứng dụng có thể giao tiếp với một ứng dụng khác qua giao thức TCP, nó phải thiết lập một kết nối logic bằng cách trao đổi các thông điệp dịch vụ theo tiêu chuẩn.

    - Nó giả định mô hình truyền thông điểm-điểm. Tức là, chỉ có hai ứng dụng có thể giao tiếp qua một kết nối duy nhất. Không có tin nhắn đa hướng nào được hỗ trợ.

    - **stream-oriented**. Điều này có nghĩa là dữ liệu đang được gửi bởi một ứng dụng đến một ứng dụng khác được giao thức diễn giải như một dòng byte. Trên thực tế, điều đó có nghĩa là nếu một ứng dụng người gửi gửi một khối dữ liệu cụ thể, không có gì đảm bảo rằng nó sẽ được gửi đến ứng dụng người nhận như cùng một khối dữ liệu trong một lượt duy nhất, tức là tin nhắn đã gửi có thể bị hỏng. thành nhiều phần như giao thức muốn và mỗi phần trong số chúng sẽ được phân phối riêng biệt, mặc dù theo đúng thứ tự.

- Giao thức UDP là một giao thức lớp truyền tải có các đặc điểm khác (theo nghĩa nào đó ngược lại) với các đặc điểm của giao thức TCP. Sau đây là các đặc điểm của nó:

    - Nó không đáng tin cậy, có nghĩa là nếu người gửi gửi tin nhắn qua giao thức UDP, không có gì đảm bảo rằng tin nhắn đó sẽ được gửi. Giao thức sẽ không cố gắng phát hiện hoặc sửa bất kỳ lỗi nào. Nhà phát triển chịu trách nhiệm cho tất cả các xử lý lỗi.

    - Nó không có kết nối, nghĩa là không cần thiết lập kết nối trước khi các ứng dụng có thể giao tiếp.

    - Nó hỗ trợ cả hai mô hình giao tiếp một-một và một-nhiều. Các thông điệp đa hướng được hỗ trợ bởi giao thức.

    - **datagram oriented**. Điều này có nghĩa là giao thức diễn giải dữ liệu dưới dạng các thông điệp có kích thước cụ thể và sẽ cố gắng phân phối chúng một cách tổng thể. Thông điệp (datagram) hoặc sẽ được gửi toàn bộ, hoặc nếu giao thức không thực hiện được điều đó sẽ không được gửi đi.

- Bởi vì giao thức UDP không đáng tin cậy, nó thường được sử dụng trong các mạng cục bộ đáng tin cậy. Để sử dụng nó cho giao tiếp qua Internet (là một mạng không đáng tin cậy), nhà phát triển phải thực hiện các cơ chế xử lý lỗi trong ứng dụng của mình.

---

## Creating an endpoint

- Một ứng dụng khách điển hình, trước khi có thể giao tiếp với ứng dụng máy chủ để sử dụng các dịch vụ của nó, phải lấy địa chỉ IP của máy chủ lưu trữ mà ứng dụng máy chủ đang chạy và số cổng giao thức được liên kết với nó. Một cặp giá trị bao gồm địa chỉ IP và số cổng giao thức xác định duy nhất một ứng dụng cụ thể đang chạy trên một máy chủ cụ thể trong mạng máy tính được gọi là **endpoint**.

- Các **endpoint** phục vụ hai mục tiêu:

    - Ứng dụng khách sử dụng một **endpoint** để chỉ định một ứng dụng máy chủ cụ thể mà nó muốn giao tiếp.

    - Ứng dụng máy chủ sử dụng một **endpoint** để chỉ định địa chỉ IP cục bộ và số cổng mà nó muốn nhận các tin nhắn đến từ các máy khách. Nếu có nhiều hơn một địa chỉ IP trên máy chủ, ứng dụng máy chủ sẽ muốn tạo một **endpoint** đặc biệt đại diện cho tất cả các địa chỉ IP cùng một lúc.

### Creating an endpoint in the client to designate the server

- Các bước cần thiết phải thực hiện trong ứng dụng khách để tạo một **endpoint** chỉ định một ứng dụng máy chủ mà máy khách muốn giao tiếp. Ban đầu, địa chỉ IP được biểu thị dưới dạng một chuỗi trong ký hiệu dấu chấm-thập phân nếu đây là địa chỉ IPv4 hoặc ở ký hiệu thập lục phân nếu đây là địa chỉ IPv6:

    - Lấy địa chỉ IP và số cổng của ứng dụng máy chủ. Địa chỉ IP phải được chỉ định dưới dạng một chuỗi trong ký hiệu dấu chấm-thập phân (IPv4) hoặc thập lục phân (IPv6).
    - Biểu diễn địa chỉ IP thô như một đối tượng của lớp địa chỉ `asio::ip::`.
    - Khởi tạo đối tượng của lớp `asio::ip::tcp::endpoint` từ đối tượng địa chỉ được tạo ở bước 2 và một số cổng.
    - **endpoint** sẵn sàng được sử dụng để chỉ định ứng dụng máy chủ trong các phương thức liên quan đến giao tiếp Boost.Asio.

[**CODE**](asio-example/chapter-1/Creating_endpoint_Client.cpp) - thực hiện trong ứng dụng khách để tạo một **endpoint** chỉ định một ứng dụng máy chủ mà ứng dụng khách muốn giao tiếp.

### Creating the server endpoint

- Các bước cần thiết để thực hiện trong ứng dụng máy chủ để tạo **endpoint** chỉ định tất cả các địa chỉ IP có sẵn trên máy chủ và số cổng mà ứng dụng máy chủ muốn lắng nghe các thông báo đến từ máy khách.

    - Lấy số cổng giao thức mà máy chủ sẽ lắng nghe các yêu cầu đến.
    - Tạo một phiên bản đặc biệt của đối tượng địa chỉ `asio::ip::` đại diện cho tất cả các địa chỉ IP có sẵn trên máy chủ đang chạy máy chủ.
    - Khởi tạo một đối tượng của lớp `asio::ip::tcp::endpoint` từ đối tượng địa chỉ được tạo ở bước 2 và một số cổng.
    - **Endpoint** sẵn sàng được sử dụng để chỉ định cho hệ điều hành mà máy chủ muốn lắng nghe các thông báo đến trên tất cả các địa chỉ IP và một số cổng giao thức cụ thể.

[**CODE**](asio-example/chapter-1/Creating_endpoint_Server.cpp) - thực hiện trong ứng dụng máy chủ để tạo một **endpoint** chỉ định tất cả các địa chỉ IP có sẵn trên máy chủ và số cổng mà ứng dụng máy chủ muốn lắng nghe các thông báo đến từ máy khách.

- Ứng dụng máy chủ thường chỉ được cung cấp số cổng giao thức mà nó sẽ lắng nghe các tin nhắn đến. Địa chỉ IP không được cung cấp vì ứng dụng máy chủ thường muốn lắng nghe các thông báo đến trên tất cả các địa chỉ IP có sẵn trên máy chủ, không chỉ trên một địa chỉ cụ thể.

- Để biểu diễn khái niệm về tất cả các địa chỉ IP có sẵn trên máy chủ, các lớp `asio::ip::address_v4` và `asio::ip::address_v6` cung cấp một phương thức tĩnh `any()`, phương thức này khởi tạo một đối tượng IP đặc biệt đại diện cho tất cả các IP có sẵn trên máy chủ.

---

## Creating an active socket

- Về cơ bản, có hai loại **socket**. Một **socket** được sử dụng để gửi và nhận dữ liệu đến và từ một ứng dụng từ xa hoặc để bắt đầu quá trình thiết lập kết nối với nó được gọi là **active socket**, trong khi **passive socket** được sử dụng để chờ thụ động các yêu cầu kết nối đến từ các ứng dụng từ xa . Các **passive socket** không tham gia vào quá trình truyền dữ liệu của người dùng.

- Các bước cần thiết để thực hiện trong một ứng dụng khách để tạo và mở một **activate socket**:

    - Tạo một đối tượng của lớp `asio::io_service` hoặc sử dụng lớp đã được tạo trước đó.
    - Tạo một đối tượng của lớp đại diện cho giao thức lớp truyền tải (TCP hoặc UDP) và phiên bản của giao thức IP bên dưới (IPv4 hoặc IPv6) mà socket được dự định giao tiếp.
    - Tạo đối tượng đại diện cho một socket tương ứng với kiểu giao thức yêu cầu. Truyền đối tượng của lớp `asio::io_service` tới phương thức khởi tạo của socket.
    - Gọi phương thức `open()` của socket, truyền đối tượng đại diện cho giao thức đã tạo ở bước 2 làm đối số.

[**CODE**](asio-example/chapter-1/Creating_an_active_socket_TCP_IPv4.cpp) - Giả định rằng socket được sử dụng để giao tiếp qua giao thức TCP và IPv4 là giao thức phía sau.

- Tại bước 1, chúng ta khởi tạo một đối tượng của lớp `asio::io_service`. Lớp này là thành phần trung tâm trong `Boost.Asio I/O infrastructure`. Nó cung cấp quyền truy cập vào các dịch vụ I/O mạng của hệ điều hành cơ bản. Các socket Boost.Asio có quyền truy cập vào các dịch vụ đó thông qua đối tượng của lớp này. Do đó, tất cả các hàm tạo lớp socket đều yêu cầu một đối tượng `asio::io_service` làm đối số. Chúng ta sẽ xem xét lớp `asio::io_service` chi tiết hơn trong các chương sau.

- Bước tiếp theo, chúng ta tạo một đối tượng của lớp `asio::ip::tcp`. Lớp này đại diện cho một giao thức TCP. Nó không cung cấp chức năng, mà hoạt động giống như một cấu trúc dữ liệu chứa một tập hợp các giá trị mô tả giao thức.

- Lớp `asio::ip::tcp` không có hàm tạo công khai. Thay vào đó, nó cung cấp hai phương thức tĩnh, `asio::ip::tcp::v4()` và `asio::ip::tcp::v6()`, trả về một đối tượng của lớp `asio::ip::tcp` đại diện cho Giao thức TCP với giao thức IPv4 hoặc IPv6 bên dưới tương ứng.

- Ở bước 3, chúng ta tạo một đối tượng của lớp `asio::ip::tcp::socket`, truyền đối tượng của lớp `asio::io_service` tới phương thức khởi tạo của nó như một đối số. Lưu ý rằng hàm tạo này không allocate đối tượng socket của hệ điều hành bên dưới. Socket của hệ điều hành thực được cấp phát trong bước 4 khi chúng ta gọi phương thức `open()` và chuyển một đối tượng chỉ định giao thức cho nó như một đối số.

- Trong `Boost.Asio`, việc mở một **socket** có nghĩa là liên kết nó với tập hợp đầy đủ các thông số mô tả một giao thức cụ thể mà **socket** được dự định giao tiếp. Khi đối tượng **socket** Boost.Asio được cung cấp các tham số này, nó có đủ thông tin để cấp phát đối tượng **socket** thực của hệ điều hành bên dưới.

- Lớp `asio::ip::tcp::socket` cung cấp một phương thức khởi tạo khác chấp nhận một đối tượng giao thức làm đối số. Hàm tạo này xây dựng một đối tượng socket và mở nó. Lưu ý rằng hàm tạo này ném một ngoại lệ của kiểu `boost::system::system_error` nếu nó không thành công. Dưới đây là một ví dụ minh họa cách chúng ta có thể kết hợp các bước 3 và 4 từ mẫu trước: [**CODE**](asio-example/chapter-1/Creating_an_active_socket_TCP_IPv4_open_in_constructor.cpp)

---

## Creating a passive socket

- **passive socket** hoặc **acceptor socket** là một loại **socket** được sử dụng để chờ các yêu cầu thiết lập kết nối từ các ứng dụng từ xa giao tiếp qua giao thức TCP. Định nghĩa này có hai hàm ý quan trọng:

    - **Passive sockets** chỉ được sử dụng trong các ứng dụng máy chủ hoặc ứng dụng kết hợp có thể đóng cả hai vai trò của máy khách và máy chủ.

    - Các **passive socket** chỉ được xác định cho giao thức TCP. Vì giao thức UDP không ngầm thiết lập kết nối, nên không cần **passive socket** khi giao tiếp được thực hiện qua UDP.

- Các bước cần thực hiện để tạo **acceptor socket**:

    - Tạo một đối tượng của lớp `asio::io_service` hoặc sử dụng lớp đã được tạo trước đó.

    - Tạo một đối tượng của lớp `asio::ip::tcp` đại diện cho giao thức TCP và phiên bản yêu cầu của giao thức IP bên dưới (IPv4 hoặc IPv6).

    - Tạo một đối tượng của lớp `asio::ip::tcp::acceptor` đại diện cho một **acceptor socket**, truyền đối tượng của lớp `asio::io_service` tới phương thức khởi tạo của nó.

    - Gọi phương thức `open()` của **acceptor socket**, truyền đối tượng đại diện cho giao thức được tạo ở bước 2 làm đối số.

[**CODE**](asio-example/chapter-1/Creating_a_passive_socket.cpp) - Giả định rằng **acceptor socket** được thiết kế để sử dụng qua giao thức TCP và IPv6 là giao thức ngầm.

- Because an **acceptor socket** is very similar to an **active socket**, the procedure of creating them is almost identical.

---

## Resolving a DNS name

- Địa chỉ IP thô rất bất tiện cho con người nhận thức và ghi nhớ, đặc biệt nếu chúng là địa chỉ IPv6.

- DNS là một hệ thống đặt tên phân tán cho phép liên kết các tên thân thiện với con người với các IP trong mạng máy tính. Tên DNS hoặc tên miền là một chuỗi đại diện cho tên của một IP trong mạng máy tính.

- DNS hoạt động như một cơ sở dữ liệu phân tán lưu trữ các ánh xạ tên DNS tới các địa chỉ IP tương ứng và cung cấp một giao diện, cho phép truy vấn các địa chỉ IP mà một tên DNS cụ thể được ánh xạ tới. Quá trình chuyển đổi tên DNS thành các địa chỉ IP tương ứng được gọi là phân giải tên miền DNS **(DNS name resolution)**. Hệ điều hành mạng hiện đại có chức năng có thể truy vấn DNS để phân giải tên DNS và cung cấp giao diện có thể được các ứng dụng sử dụng để thực hiện phân giải tên DNS.

- Khi được cấp một tên DNS, trước khi một máy khách có thể giao tiếp với một ứng dụng máy chủ tương ứng, trước tiên nó phải phân giải tên đó để có được các địa chỉ IP được liên kết với tên đó.

- Các bước cần thiết để thực hiện trong ứng dụng khách nhằm phân giải tên DNS để lấy địa chỉ IP (không hoặc nhiều hơn) của các máy chủ (không hoặc nhiều hơn) đang chạy ứng dụng máy chủ mà ứng dụng khách muốn giao tiếp:

    - Lấy tên DNS và số cổng giao thức chỉ định ứng dụng máy chủ và biểu diễn chúng dưới dạng chuỗi.

    - Tạo một dối tượng của lớp `asio::io_service` hoặc sử dụng lớp đã được tạo trước đó.

    - Tạo một đối tượng của lớp `resolver::query` đại diện cho một truy vấn phân giải tên DNS.

    - Tạo một dối tượng của lớp trình phân giải tên DNS phù hợp với giao thức cần thiết.

    - Gọi phương thức quyết định () của trình phân giải, chuyển một đối tượng truy vấn được tạo ở bước 3 cho nó làm đối số.

[**CODE**](asio-example/chapter-1/Resolving_a_DNS_name_TCP.cpp) - Giả định rằng ứng dụng khách nhằm giao tiếp với ứng dụng máy chủ qua giao thức TCP và IPv6 là giao thức ngầm. Bên cạnh đó, giả định rằng tên DNS máy chủ và số cổng đã được ứng dụng khách lấy và biểu diễn dưới dạng chuỗi:

[**CODE**](asio-example/chapter-1/Resolving_a_DNS_name_UDP.cpp) - Giả định rằng ứng dụng khách nhằm giao tiếp với ứng dụng máy chủ qua giao thức TCP và IPv6 là giao thức ngầm.

---

## Binding a socket to an endpoint

- Trước khi **activate socket** có thể giao tiếp với ứng dụng từ xa hoặc **passive socket** có thể chấp nhận các yêu cầu kết nối đến, chúng phải được liên kết với một địa chỉ IP cục bộ cụ thể (hoặc nhiều địa chỉ) và số cổng giao thức, nghĩa là một **endpoint**. Quá trình liên kết một socket với một **endpoint** cụ thể được gọi là **binding**. Khi một **socket** được liên kết với một **endpoint**, tất cả các **packet** đi vào máy chủ từ mạng với **endpoint** đó làm địa chỉ đích của chúng sẽ được hệ điều hành chuyển hướng đến **socket** cụ thể đó. Tương tự như vậy, tất cả dữ liệu đi ra từ một **socket** được liên kết với một **endpoint** cụ thể sẽ được xuất từ ​​máy chủ tới mạng thông qua một giao diện mạng được liên kết với địa chỉ IP tương ứng được chỉ định trong **endpoint** đó.

- Khi liên kết **socket** được ủy quyền cho hệ điều hành, không có gì đảm bảo rằng nó sẽ được liên kết với cùng một **endpoint** mỗi lần. Ngay cả khi có một giao diện mạng duy nhất và một địa chỉ IP trên máy chủ, **socket** có thể được liên kết với một số cổng giao thức khác nhau mỗi khi thực hiện **binding** ngầm định.

- Không giống như các ứng dụng khách thường không quan tâm đến địa chỉ IP và số cổng giao thức mà **activate socket** của nó sẽ giao tiếp với ứng dụng từ xa, ứng dụng máy chủ thường cần liên kết **socket** bộ nhận của nó với một **endpoint** cụ thể một cách rõ ràng. Điều này được giải thích bởi thực tế là tất cả các máy khách muốn giao tiếp với nó phải biết **endpoint** của máy chủ và phải giữ nguyên sau khi ứng dụng máy chủ được khởi động lại.

- Các bước cần thiết để tạo **acceptor socket** và liên kết nó với một **endpoint** chỉ định tất cả các địa chỉ IP có sẵn trên máy chủ và một số cổng giao thức cụ thể trong ứng dụng máy chủ IPv4 TCP:
    
    - Lấy số cổng giao thức mà máy chủ sẽ lắng nghe các yêu cầu kết nối đến.

    - Tạo một **endpoint** đại diện cho tất cả các địa chỉ IP có sẵn trên máy chủ và số cổng giao thức có được ở bước 1.

    - Tạo và mở **acceptor socket**.

    - Gọi phương thức `bind()` của **acceptor socket**, truyền đối tượng **endpoint** làm đối số cho nó.

[**CODE**](asio-example/chapter-1/Binding_a_socket_TCP_passive.cpp) - Giả định rằng số cổng giao thức đã được ứng dụng lấy.

- Việc **binding** được thực hiện ở bước 4. Đây là một thao tác khá đơn giản. Chúng ta gọi phương thức **bind()** của **acceptor socket**, truyền một đối tượng đại diện cho một **endpoint** mà nơi **acceptor socket** phải được **binding** như một đối số của phương thức. Nếu hàm thành công, **acceptor socket** được liên kết với **endpoint** tương ứng và sẵn sàng bắt đầu lắng nghe các yêu cầu kết nối đến trên **endpoint** đó.

- Máy chủ UDP không thiết lập kết nối và sử dụng các **activate socket** để chờ các yêu cầu đến. Quá trình liên kết một **activate socket** rất giống với việc liên kết một **acceptor socket**. Ở đây, chúng ta trình bày [**CODE demo**](asio-example/chapter-1/Binding_a_socket_UDP_active.cpp) cách liên kết một **activate socket** UDP với một **endpoint** chỉ định tất cả các địa chỉ IP có sẵn trên máy chủ và một số cổng giao thức cụ thể.

---

## Connecting a socket

- Trước khi một socket TCP có thể được sử dụng để giao tiếp với một ứng dụng từ xa, nó phải thiết lập một kết nối logic với nó. Theo giao thức TCP, quá trình thiết lập kết nối nằm trong việc trao đổi các thông điệp dịch vụ giữa hai ứng dụng, nếu thành công, kết quả là hai ứng dụng được kết nối logic và sẵn sàng giao tiếp với nhau.

- Đại khái, quá trình thiết lập kết nối trông như thế này. Ứng dụng khách, khi nó muốn giao tiếp với ứng dụng máy chủ, sẽ tạo và mở một **activate socket** và đưa ra lệnh `connect()` trên đó, chỉ định một ứng dụng máy chủ đích với một đối tượng **endpoint**. Điều này dẫn đến thông báo yêu cầu thiết lập kết nối được gửi đến ứng dụng máy chủ qua mạng. Ứng dụng máy chủ nhận yêu cầu và tạo một **activate socket** ở phía bên của nó, đánh dấu nó là đã kết nối với một máy khách cụ thể và trả lời lại máy khách với thông báo xác nhận rằng kết nối đã được thiết lập thành công ở phía máy chủ. Tiếp theo, máy khách đã nhận được xác nhận từ máy chủ, đánh dấu socket của nó là đã kết nối với máy chủ và gửi thêm một thông báo tới nó để xác nhận rằng kết nối đã được thiết lập thành công ở phía máy khách. Khi máy chủ nhận được thông báo xác nhận từ máy khách, kết nối logic giữa hai ứng dụng được coi là đã thiết lập.

- Mô hình giao tiếp điểm-điểm được giả định giữa hai socket được kết nối. Điều này có nghĩa là nếu socket A được kết nối với socket B, cả hai chỉ có thể giao tiếp với nhau và không thể giao tiếp với bất kỳ socket nào khác C. Trước khi socket A có thể giao tiếp với socket C, nó phải đóng kết nối với socket B và thiết lập một kết nối mới với socket C.

- Các bước cần thiết để thực hiện trong ứng dụng khách TCP để kết nối **activate socket** với ứng dụng máy chủ:

    - Lấy địa chỉ IP của ứng dụng máy chủ đích và số cổng giao thức.

    - Tạo một đối tượng của lớp `asio::ip::tcp::endpoint` từ địa chỉ IP và số cổng giao thức có được ở bước 1.

    - Tạo và mở một **socket** đang hoạt động.

    - Gọi phương thức `connect()` của socket chỉ định đối tượng **endpoint** được tạo ở bước 2 làm đối số.

    - Nếu phương pháp thành công, **socket** được coi là đã kết nối và có thể được sử dụng để gửi và nhận dữ liệu đến và đi từ máy chủ.

[**CODE**](asio-example/chapter-1/Connecting_a_socket.cpp) - thực hiện trong ứng dụng khách TCP để kết nối **activate socket** với ứng dụng máy chủ.

[**CODE**](asio-example/chapter-1/Connecting_a_socket_DNS_name.cpp) - kết nối một **socket** với một máy chủ ứng dụng được đại diện bằng tên DNS và số cổng giao thức.

- Trong bước 4, chúng ta gọi phương thức `connect()` của socket, truyền một đối tượng **endpoint** chỉ định máy chủ đích cho nó làm đối số. Chức năng này kết nối **socket** với máy chủ. Kết nối được thực hiện đồng bộ, có nghĩa là phương thức chặn luồng người gọi cho đến khi hoạt động kết nối được thiết lập hoặc xảy ra lỗi.

- Lưu ý rằng chúng ta không liên kết socket với bất kỳ **endpoint** cục bộ nào trước khi kết nối nó. Điều này không có nghĩa là **socket** vẫn không bị **binding**. Trước khi thực hiện quy trình thiết lập kết nối, phương thức `connect()` của **socket** sẽ liên kết **socket** với **endpoint** bao gồm địa chỉ IP và số cổng giao thức do hệ điều hành chọn.

- Một điều khác cần lưu ý trong ví dụ này là chúng ta sử dụng quá tải phương thức `connect()` ném ngoại lệ của kiểu `boost::system::system_error` nếu hoạt động không thành công và quá tải `asio::ip::address::from_string()` phương thức mà chúng ta sử dụng ở bước 2. Do đó, cả hai lệnh gọi đều được bao bọc trong một khối try.

---

## Accepting connections

- Khi ứng dụng khách muốn giao tiếp với ứng dụng máy chủ qua giao thức TCP, trước tiên nó cần thiết lập một kết nối logic với máy chủ đó. Để làm điều đó, máy khách allocates một **activate socket** và đưa ra lệnh kết nối trên đó (ví dụ: bằng cách gọi phương thức `connect()` trên đối tượng ổ cắm), dẫn đến một thông báo yêu cầu thiết lập kết nối được gửi đến máy chủ.

- Về phía máy chủ, một số sắp xếp phải được thực hiện trước khi ứng dụng máy chủ có thể chấp nhận và xử lý các yêu cầu kết nối đến từ máy khách. Trước đó, tất cả các yêu cầu kết nối được nhắm mục tiêu vào ứng dụng máy chủ này đều bị hệ điều hành từ chối.

- Đầu tiên, ứng dụng máy chủ tạo và mở một **acceptor socket** và liên kết nó với **endpoint** cụ thể. Tại thời điểm này, các yêu cầu kết nối của khách hàng đến **endpoint** của **acceptor  socket** vẫn bị hệ điều hành từ chối. Để hệ điều hành bắt đầu chấp nhận các yêu cầu kết nối được nhắm mục tiêu tại **endpoint** cụ thể được liên kết với **acceptor socket** cụ thể, **acceptor socket** đó phải được chuyển sang chế độ lắng nghe. Sau đó, hệ điều hành phân bổ một hàng đợi cho các yêu cầu kết nối đang chờ xử lý được liên kết với **acceptor socket** này và bắt đầu chấp nhận yêu cầu kết nối được gửi đến nó. Hàng đợi yêu cầu được liên kết với một **acceptor  socket** là mục tiêu của yêu cầu kết nối. Khi ở trong hàng đợi, yêu cầu kết nối có sẵn để ứng dụng máy chủ xử lý. Ứng dụng máy chủ, khi sẵn sàng xử lý yêu cầu kết nối tiếp theo, deque một yêu cầu và xử lý nó.

- Lưu ý rằng **acceptor socket** chỉ được sử dụng để thiết lập kết nối với các ứng dụng khách và không được sử dụng trong quá trình giao tiếp tiếp theo. Khi xử lý một yêu cầu kết nối đang chờ xử lý, **acceptor socket** sẽ phân bổ một **activate socket** mới, liên kết nó với một **endpoint** do hệ điều hành chọn và kết nối nó với ứng dụng khách tương ứng đã đưa ra yêu cầu kết nối đó. Sau đó, **activate socket** mới này đã sẵn sàng được sử dụng để giao tiếp với máy khách. **acceptor socket** sẽ khả dụng để xử lý yêu cầu kết nối đang chờ xử lý tiếp theo.

- Công thức này mô tả cách chuyển một **acceptor socket** sang chế độ lắng nghe và chấp nhận các yêu cầu kết nối đến trong ứng dụng máy chủ TCP bằng Boost.Asio.

- Cách thiết lập **acceptor socket** để nó bắt đầu lắng nghe các kết nối đến và sau đó cách sử dụng nó để xử lý đồng bộ yêu cầu kết nối đang chờ xử lý.

    - Lấy số cổng mà máy chủ sẽ nhận các yêu cầu kết nối đến.
    
    - Tạo **endpoint** máy chủ.
    
    - Khởi tạo và mở **acceptor socket**.
    
    - Ràng buộc **acceptor socket** với **endpoint** máy chủ được tạo ở bước 2.
    
    - Gọi phương thức `listen()` của ổ cắm chấp nhận để làm cho nó bắt đầu lắng nghe các yêu cầu kết nối đến trên **endpoint**.
    
    - Khởi tạo một đối tượng **active socket**.
    
    - Khi đã sẵn sàng để xử lý một yêu cầu kết nối, hãy gọi phương thức `accept()` của ổ cắm chấp nhận chuyển đối tượng **active socket** được tạo ở bước 6 làm đối số.
    
    - Nếu hàm thành công, **active socket** được kết nối với ứng dụng khách và sẵn sàng được sử dụng để giao tiếp với nó.

[**CODE**](asio-example/chapter-1/Accepting_a_connection.cpp) - Giả định rằng chỉ một kết nối đến sẽ được xử lý ở chế độ đồng bộ.

- Trong bước 5, chúng ta gọi phương thức `listen()` của `acceptor` truyền giá trị hằng số `BACKLOG_SIZE` làm đối số. Hàm này chuyển **acceptor socket** sang trạng thái mà nó sẽ lắng nghe các yêu cầu kết nối đến. Nếu chúng ta không gọi phương thức `listen()` trên đối tượng acceptor, tất cả các yêu cầu kết nối đến **endpoint** tương ứng sẽ bị hệ điều hành từ chối. Ứng dụng phải thông báo rõ ràng cho hệ điều hành rằng nó muốn bắt đầu lắng nghe các yêu cầu kết nối đến trên **endpoint** cụ thể bằng hàm này.

- Đối số mà phương thức `listen()` chấp nhận chỉ định kích thước của hàng đợi được duy trì bởi hệ điều hành mà nó đặt các yêu cầu kết nối đến từ các máy khách. Các yêu cầu nằm trong hàng đợi và đang đợi ứng dụng máy chủ xếp hàng và xử lý chúng. Khi hàng đợi đầy, các yêu cầu kết nối mới sẽ bị hệ điều hành từ chối

- Trong bước 6, chúng ta tạo một đối tượng **active socket** mà **_không cần mở_** nó. Chúng tôi sẽ cần nó trong bước 7.

- Trong bước 7, chúng ta gọi phương thức `accept()` của **acceptor socket**. Phương thức này chấp nhận một **active socket** như một đối số và thực hiện một số hoạt động. Đầu tiên, nó kiểm tra hàng đợi được liên kết với **acceptor socket** có chứa các yêu cầu kết nối đang chờ xử lý. Nếu hàng đợi trống, phương thức sẽ chặn thực thi cho đến khi một yêu cầu kết nối mới đến **endpoint** mà **acceptor socket** đang **binding** và hệ điều hành đưa nó vào hàng đợi.

- Nếu ít nhất một yêu cầu kết nối có sẵn trong hàng đợi, yêu cầu ở trên cùng của hàng đợi sẽ được trích ra và được xử lý. **Active socket** được chuyển đến phương thức `accept()` làm đối số được kết nối với ứng dụng khách tương ứng đã đưa ra yêu cầu kết nối.

- Nếu quá trình thiết lập kết nối thành công, phương thức `accept()` trở lại và **active socket** được mở và kết nối với ứng dụng khách và có thể được sử dụng để gửi dữ liệu đến và nhận dữ liệu từ nó.

- Hãy nhớ rằng **acceptor socket** không tự kết nối với ứng dụng khách trong khi xử lý yêu cầu kết nối. Thay vào đó, nó sẽ mở và kết nối một **active socket** khác, **socket** này sau đó được sử dụng để giao tiếp với ứng dụng khách. **Acceptor socket** chỉ lắng nghe và xử lý (chấp nhận) các yêu cầu kết nối đến.

- Lưu ý rằng máy chủ UDP không sử dụng **acceptor socket** vì giao thức UDP không ngầm thiết lập kết nối. Thay vào đó, một **active socket** được sử dụng được liên kết với một **endpoint** và lắng nghe các thông báo I/O đến và cùng một **active socket** này được sử dụng để giao tiếp.
